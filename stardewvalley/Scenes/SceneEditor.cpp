#include "stdafx.h"
#include "SceneEditor.h"
#include "Framework.h"
#include "UiButton.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include "TileMap.h"
#include "RectangleGo.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "TextGo.h"
#include "StringTable.h"
#include "DataTableMgr.h"
#include "rapidcsv.h"

SceneEditor::SceneEditor()
	:Scene(SceneId::Editor)
{
	//resourceListPath = "scripts/defaultResourceList.csv";
}

void SceneEditor::Init()
{
	Release();

	auto size = FRAMEWORK.GetWindowSize();
	centerPos = size * 0.5f;

	//맵툴 ui 배경
	palletBg = (TileMap*)AddGo(new TileMap("map/walls_and_floors.png", "palletBg"));
	palletBg->setTexSize(32.f, 32.f);
	palletBg->setTilesize(96.f, 96.f);
	palletBg->Load(7, 20, 64.f, 528.f);
	palletBg->SetOrigin(Origins::TL);
	palletBg->SetPosition(0, 0);
	palletBg->sortLayer = 100;

	/*----행열 조절----*/
	//행열 조절, 맵 생성 버튼
	buttonCreate = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "ok", "ok"));

	buttonCreate->SetOrigin(Origins::ML);
	buttonCreate->sortLayer = 101;
	buttonCreate->OnClick = [this]()
	{
		TileMap* tempFarmMapT1 = (TileMap*)AddGo(new TileMap("map/spring_outdoorsTileSheet_cut.png", "MapTile1"));
		tempFarmMapT1->Reset();
		tempFarmMapT1->Load(col, row, 48.f, 0.f);

		TileMap* tempFarmMapT2 = (TileMap*)AddGo(new TileMap("map/spring_outdoorsTileSheet_cut.png", "MapTile2"));
		tempFarmMapT2->Reset();
		tempFarmMapT2->Load(col, row, 176.f, 0.f); //투명한 타일 176, 0

		TileMap* tempFarmMapObj = (TileMap*)AddGo(new TileMap("map/object.png", "MapObj"));
		tempFarmMapObj->Reset();
		tempFarmMapObj->Load(col, row, 96, 16); //투명한 타일 96, 16

		if (farmMapT1 != nullptr)
		{
			RemoveGo(farmMapT1);
			delete farmMapT1;
			farmMapT1 = nullptr;
		}

		if (farmMapT2 != nullptr)
		{
			RemoveGo(farmMapT2);
			delete farmMapT2;
			farmMapT2 = nullptr;
		}

		if (farmMapObj != nullptr)
		{
			RemoveGo(farmMapObj);
			delete farmMapObj;
			farmMapObj = nullptr;
		}
		
		farmMapT1 = tempFarmMapT1;
		farmMapT1->SetOrigin(Origins::MC);
		farmMapT1->SetPosition(centerPos.x + 500.f, centerPos.y);

		farmMapT2 = tempFarmMapT2;
		farmMapT2->SetOrigin(Origins::MC);
		farmMapT2->SetPosition(farmMapT1->GetPosition());

		farmMapObj = tempFarmMapObj;
		farmMapObj->SetOrigin(Origins::MC);
		farmMapObj->SetPosition(farmMapT1->GetPosition());

		MapLT = { farmMapT1->vertexArray.getBounds().left, farmMapT1->vertexArray.getBounds().top };
		MapSize = farmMapT1->GetTileMapSize();
		farmMapT1->sortLayer = -1;

		selectMap = farmMapT1;
		curTile = selectTile;
		IsCollActive = false;
		SetColliders();
		SetCanFarms();
	};

	buttonColUp = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowUp", "arrowUp"));
	buttonColUp->SetOrigin(Origins::BC);
	buttonColUp->sortLayer = 101;
	buttonColUp->OnClick = [this]()
	{
		col++;
		colText->SetString(to_string(col));
		colText->SetOrigin(Origins::BC);
		colText->SetPosition(buttonColUp->GetPosition().x, numUI->GetPosition().y - 13.f);
	};

	buttonColDown = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowDown", "arrowDown"));
	buttonColDown->SetOrigin(Origins::TC);
	buttonColDown->sortLayer = 101;
	buttonColDown->OnClick = [this]()
	{
		if (col > 1)
		{
			col--;
			colText->SetString(to_string(col));
			colText->SetOrigin(Origins::BC);
			colText->SetPosition(buttonColUp->GetPosition().x, numUI->GetPosition().y - 13.f);
		}
	};
	
	buttonRowUp = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowUp", "arrowUp"));
	buttonRowUp->SetOrigin(Origins::BC);
	buttonRowUp->sortLayer = 101;
	buttonRowUp->OnClick = [this]()
	{
		row++;
		rowText->SetString(to_string(row));
		rowText->SetOrigin(Origins::BC);
		rowText->SetPosition(buttonRowUp->GetPosition().x, numUI->GetPosition().y - 13.f);
	};

	buttonRowDown = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowDown", "arrowDown"));
	buttonRowDown->SetOrigin(Origins::TC);
	buttonRowDown->sortLayer = 101;
	buttonRowDown->OnClick = [this]()
	{
		if (row > 1)
		{
			row--;
			rowText->SetString(to_string(row));
			rowText->SetOrigin(Origins::BC);
			rowText->SetPosition(buttonRowUp->GetPosition().x, numUI->GetPosition().y - 13.f);
		}
	};

	numUI = (SpriteGo*)AddGo(new SpriteGo("graphics/numUI.png", "numUI"));
	numUI->sortLayer = 101;
	numUI->SetOrigin(Origins::ML);
	numUI->SetScale({ 4.f, 4.f });

	//행열 텍스트
 	colText = (TextGo*)AddGo(new TextGo("colText", "fonts/SDMiSaeng.ttf")); //열, x
	rowText = (TextGo*)AddGo(new TextGo("colText", "fonts/SDMiSaeng.ttf")); //행, y

	//커서가 올라간 타일
	selectTile = (SpriteGo*)AddGo(new SpriteGo("map/spring_outdoorsTileSheet_cut.png", "selectTile"));
	selectTile->SetScale(tileScale);
	selectTile->SetOrigin(Origins::TL);
	sf::IntRect texRect(0, 0, 16, 16);
 	selectTile->sprite.setTextureRect(texRect);
	selectTile->SetActive(false);
	selectTile->sortLayer = 3;

	//선택된 오브젝트 타일
	selectObj = (SpriteGo*)AddGo(new SpriteGo("map/object.png", "selectObj"));
	selectObj->SetScale(tileScale);
	selectObj->SetOrigin(Origins::TL);
	selectObj->sprite.setTextureRect(texRect);
	selectObj->SetActive(false);
	selectObj->sortLayer = 3;

	selColl = (RectangleGo*)AddGo(new RectangleGo(tilesize));
	selColl->SetOrigin(Origins::TL);
	selColl->rectangle.setFillColor(sf::Color(0, 84, 255, 128));
	selColl->sortLayer = 3;
	selColl->SetActive(false);

	//타이틀로 돌아가는 버튼
	buttonBack = (UiButton*)AddGo(new UiButton("graphics/TitleButtons.ko-KR.png", "back1", "back1"));
	buttonBack->SetOrigin(Origins::ML);
	buttonBack->sortLayer = 101;
	buttonBack->SetScale({ 2.f,2.f });
	buttonBack->OnClick = [this]()
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	};

	buttonBack->OnEnter = [this]()
	{
		buttonBack->sprite.setTextureRect(RESOURCE_MGR.GetTextureRect("back2"));
	};

	buttonBack->OnExit = [this]()
	{
		buttonBack->sprite.setTextureRect(RESOURCE_MGR.GetTextureRect("back1"));
	};

	/*----타일 팔레트----*/
	tilePallet = (SpriteGo*)AddGo(new SpriteGo("map/spring_outdoorsTileSheet_cut.png", "tilePallet"));
	tilePallet->SetOrigin(Origins::TL);
	tilePallet->sortLayer = 101;
	tilePallet->SetScale({ 3.f, 3.f });
	tilePallet->sprite.setTextureRect(RESOURCE_MGR.GetTextureRect("pallet1"));

	ObjPallet = (SpriteGo*)AddGo(new SpriteGo("map/object.png", "objPallet"));
	ObjPallet->SetOrigin(Origins::TL);
	ObjPallet->sortLayer = 101;
	ObjPallet->SetScale({ 3.f, 3.f });
	ObjPallet->SetActive(false);

	selPalTile = (RectangleGo*)AddGo(new RectangleGo(palletTileSize));
	selPalTile->rectangle.setFillColor(sf::Color::Transparent);
	selPalTile->SetOrigin(Origins::TL);
	selPalTile->rectangle.setOutlineThickness(2.f);
	selPalTile->rectangle.setOutlineColor(sf::Color::White);
	selPalTile->sortLayer = 102;
	selPalTile->SetActive(false);

	buttonPalL = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowLeft", "arrowLeft"));
	buttonPalL->SetOrigin(Origins::TL);
	buttonPalL->sortLayer = 101;
	buttonPalL->OnClick = [this]()
	{
		if (palNum > 1)
		{
			palNum--;
			ChangePallet();
		}
	};

	buttonPalR = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowRight", "arrowRight"));
	buttonPalR->SetOrigin(Origins::TL);
	buttonPalR->sortLayer = 101;
	buttonPalR->OnClick = [this]()
	{
		if (palNum < 4)
		{
			palNum++;
			ChangePallet();
		}
	};

	/*----맵 레이어 변경----*/
	//버튼
	buttonLayer1 = (UiButton*)AddGo(new UiButton("graphics/uiBox.png", "layerUI1"));
	buttonLayer1->sortLayer = 101;
	buttonLayer1->SetScale({ 3.f, 3.f });
	buttonLayer1->OnClick = [this]()
	{
		curTile = selectTile;
		selectMap = farmMapT1;
		currentLayer = 0;
		nowLayer->SetString("current layer: " + GetCurrentLayer());
		if (ObjPallet->GetActive())
		{
			ObjPallet->SetActive(false);
			tilePallet->SetActive(true);
		}
	};

	buttonLayer2 = (UiButton*)AddGo(new UiButton("graphics/uiBox.png", "layerUI2"));
	buttonLayer2->sortLayer = 101;
	buttonLayer2->SetScale({ 3.f, 3.f });
	buttonLayer2->OnClick = [this]()
	{
		curTile = selectTile;
		selectMap = farmMapT2;
		currentLayer = 1;
		nowLayer->SetString("current layer: " + GetCurrentLayer());
		if (ObjPallet->GetActive())
		{
			ObjPallet->SetActive(false);
			tilePallet->SetActive(true);
		}
	};

	buttonLayerObj = (UiButton*)AddGo(new UiButton("graphics/uiBox.png", "layerUIObj"));
	buttonLayerObj->sortLayer = 101;
	buttonLayerObj->SetScale({ 3.f, 3.f });
	buttonLayerObj->OnClick = [this]()
	{
		selectMap = farmMapObj;
		selPallet = ObjPallet;
		curTile = selectObj;
		currentLayer = 2;
		nowLayer->SetString("current layer: " + GetCurrentLayer());
		if (tilePallet->GetActive())
		{
			tilePallet->SetActive(false);
			ObjPallet->SetActive(true);
		}
	};

	buttonLayerColl = (UiButton*)AddGo(new UiButton("graphics/uiBox.png", "layerUIColl"));
	buttonLayerColl->sortLayer = 101;
	buttonLayerColl->SetScale({ 3.f, 3.f });
	buttonLayerColl->OnClick = [this]()
	{
		IsCollActive = !IsCollActive;
		for (auto rect : colliders)
		{
			rect->SetActive(IsCollActive);
		}
		if (IsCollActive)
		{
			selectMap = farmMapColl;
			currentLayer = 3;
		}
		else
		{
			selectMap = farmMapT1;
			currentLayer = 0;
			if (ObjPallet->GetActive())
			{
				ObjPallet->SetActive(false);
				tilePallet->SetActive(true);
			}
		}
		if (IsFarmActive)
		{
			IsFarmActive = false;
			for (auto rect : canFarms)
			{
				rect->SetActive(false);
			}
		}
		nowLayer->SetString("current layer: " + GetCurrentLayer());
	}; 

	buttonLayerFarm= (UiButton*)AddGo(new UiButton("graphics/BigUiBox.png", "layerUIFarm"));
	buttonLayerFarm->sortLayer = 101;
	buttonLayerFarm->SetScale({ 3.f, 3.f });
	buttonLayerFarm->OnClick = [this]()
	{
		IsFarmActive = !IsFarmActive;
		for (auto rect : canFarms)
		{
			rect->SetActive(IsFarmActive);
		}
		if (IsFarmActive)
		{
			selectMap = farmMapCanFarm;
			currentLayer = 4;
		}
		else
		{
			selectMap = farmMapT1;
			currentLayer = 0;
			if (ObjPallet->GetActive())
			{
				ObjPallet->SetActive(false);
				tilePallet->SetActive(true);
			}
		}
		if (IsCollActive)
		{
			IsCollActive = false;
			for (auto rect : colliders)
			{
				rect->SetActive(false);
			}
		}
		nowLayer->SetString("current layer: " + GetCurrentLayer());
	};

	//텍스트
	Layer1 = (TextGo*)AddGo(new TextGo("Layer1Text", "fonts/SDMiSaeng.ttf"));
	Layer1->text.setOutlineThickness(1.f);
	Layer1->text.setOutlineColor(sf::Color::Black);

	Layer2 = (TextGo*)AddGo(new TextGo("Layer2Text", "fonts/SDMiSaeng.ttf"));
	Layer2->text.setOutlineThickness(1.f);
	Layer2->text.setOutlineColor(sf::Color::Black);

	LayerObj = (TextGo*)AddGo(new TextGo("LayerObjText", "fonts/SDMiSaeng.ttf"));
	LayerObj->text.setOutlineThickness(1.f);
	LayerObj->text.setOutlineColor(sf::Color::Black);

	LayerColl = (TextGo*)AddGo(new TextGo("LayerCollText", "fonts/SDMiSaeng.ttf"));
	LayerColl->text.setOutlineThickness(1.f);
	LayerColl->text.setOutlineColor(sf::Color::Black);

	LayerFarm = (TextGo*)AddGo(new TextGo("LayerCollText", "fonts/SDMiSaeng.ttf"));
	LayerFarm->text.setOutlineThickness(1.f);
	LayerFarm->text.setOutlineColor(sf::Color::Black);

	/*----세이브로드----*/
	buttonSave = (UiButton*)AddGo(new UiButton("graphics/setButton.png", "buttonSave"));
	buttonSave->sortLayer = 101;
	buttonSave->SetScale({ 0.5f, 0.5f });
	buttonSave->OnClick = [this]()
	{
		
		if (farmMapT1->Save("tables/newMapLayer1.csv"))
		{
			cout << "레이어1 세이브 성공" << endl;
		}
		else
		{
			cout << "레이어1 세이브 실패" << endl;
		}
		if (farmMapT2->Save("tables/newMapLayer2.csv"))
		{
			cout << "레이어2 세이브 성공" << endl;
		}
		else
		{
			cout << "레이어2 세이브 실패" << endl;
		}
		if (farmMapObj->Save("tables/newMapLayerObj.csv"))
		{
			SaveObject("tables/newMapObj.csv");
			cout << "오브젝트 레이어 세이브 성공" << endl;
		}
		else
		{
			cout << "오브젝트 레이어 세이브 실패" << endl;
		}
		if (SaveCollider("tables/newMapCollider.csv"))
		{
			cout << "충돌체 레이어 세이브 성공" << endl;
		}
		else
		{
			cout << "충돌체 레이어 세이브 실패" << endl;
		}
		if (SaveCanFarm("tables/newMapCanFarm.csv"))
		{
			cout << "농사 불가능 레이어 세이브 성공" << endl;
		}
		else
		{
			cout << "농사 불가능 레이어 세이브 실패" << endl;
		}
		
	};

	buttonLoad = (UiButton*)AddGo(new UiButton("graphics/setButton.png", "buttonSave"));
	buttonLoad->sortLayer = 101;
	buttonLoad->SetScale({ 0.5f, 0.5f });
	buttonLoad->OnClick = [this]()
	{
		IsCollActive = false;
		IsFarmActive = false;

		TileMap* tempFarmMapT1 = (TileMap*)AddGo(new TileMap("map/spring_outdoorsTileSheet_cut.png", "MapTile1"));
		tempFarmMapT1->Reset();
		tempFarmMapT1->Load("tables/newMapLayer1.csv");

		TileMap* tempFarmMapT2 = (TileMap*)AddGo(new TileMap("map/spring_outdoorsTileSheet_cut.png", "MapTile2"));
		tempFarmMapT2->Reset();
		tempFarmMapT2->Load("tables/newMapLayer2.csv"); //투명한 타일 176, 0

		TileMap* tempFarmMapObj = (TileMap*)AddGo(new TileMap("map/object.png", "MapObj"));
		tempFarmMapObj->Reset();
		tempFarmMapObj->Load("tables/newMapLayerObj.csv"); //투명한 타일 96, 16

		if (farmMapT1 != nullptr)
		{
			RemoveGo(farmMapT1);
			delete farmMapT1;
			farmMapT1 = nullptr;
		}

		if (farmMapT2 != nullptr)
		{
			RemoveGo(farmMapT2);
			delete farmMapT2;
			farmMapT2 = nullptr;
		}

		if (farmMapObj != nullptr)
		{
			RemoveGo(farmMapObj);
			delete farmMapObj;
			farmMapObj = nullptr;
		}

		farmMapT1 = tempFarmMapT1;
		farmMapT1->SetOrigin(Origins::MC);
		farmMapT1->SetPosition(centerPos.x + 500.f, centerPos.y);

		farmMapT2 = tempFarmMapT2;
		farmMapT2->SetOrigin(Origins::MC);
		farmMapT2->SetPosition(farmMapT1->GetPosition());

		farmMapObj = tempFarmMapObj;
		farmMapObj->SetOrigin(Origins::MC);
		farmMapObj->SetPosition(farmMapT1->GetPosition());

		MapLT = { farmMapT1->vertexArray.getBounds().left, farmMapT1->vertexArray.getBounds().top };
		MapSize = farmMapT1->GetTileMapSize();
		farmMapT1->sortLayer = -1;

		selectMap = farmMapT1;
		curTile = selectTile;

		col = farmMapT1->GetSize().x;
		row = farmMapT1->GetSize().y;

		colText->SetString(to_string(col));
		rowText->SetString(to_string(row));

		SetColliders();
		LoadCollider("tables/newMapCollider.csv");
		for (int i = 0; i < tempcolliders.size(); i++)
		{
			int index = tempcolliders[i].indexY * col + tempcolliders[i].indexX;
			colliders[index]->rectangle.setOutlineColor(sf::Color(255, 0, 0, 255));
			colliders[index]->rectangle.setFillColor(sf::Color(255, 0, 0, 70));
		}

		LoadObject("tables/newMapObj.csv");

		SetCanFarms();
		LoadCanFarm("tables/newMapCanFarm.csv");
		for (int i = 0; i < tempCanFarm.size(); i++)
		{
			if (!tempCanFarm[i].canFarm)
			{
				int index = tempCanFarm[i].indexY * col + tempCanFarm[i].indexX;
				canFarms[index]->rectangle.setOutlineColor(sf::Color(255, 0, 0, 255));
				canFarms[index]->rectangle.setFillColor(sf::Color(95, 0, 255, 70));
			}
		}
		
	};

	saveText = (TextGo*)AddGo(new TextGo("saveText", "fonts/SDMiSaeng.ttf"));
	saveText->text.setOutlineThickness(1.f);
	saveText->text.setOutlineColor(sf::Color::Black);

	loadText = (TextGo*)AddGo(new TextGo("saveText", "fonts/SDMiSaeng.ttf"));
	loadText->text.setOutlineThickness(1.f);
	loadText->text.setOutlineColor(sf::Color::Black);

	nowLayer = (TextGo*)AddGo(new TextGo("nowLayer", "fonts/SDMiSaeng.ttf"));
	nowLayer->text.setOutlineThickness(1.f);
	nowLayer->text.setOutlineColor(sf::Color::Black);

	for (auto go : gameObjects)
	{
		go->Init();
	}
	
}

void SceneEditor::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneEditor::Enter()
{
	Scene::Enter();

	auto size = FRAMEWORK.GetWindowSize();
	centerPos = size * 0.5f;

	worldView.setSize(size);
	worldView.setCenter(centerPos);
	WVcenterPos = centerPos;

	uiView.setSize(size);
	uiView.setCenter(centerPos);

	/*---변수 초기화---*/
	palNum = 1;
	palNumX = 0;
	palNumY = 0;
	currentLayer = 0;

	selPallet = tilePallet;

	/*---행열 조절---*/
	//버튼ui
	numUI->SetPosition(48.f, 72.f + numUI->sprite.getGlobalBounds().height / 2);

	buttonCreate->SetPosition(numUI->GetPosition().x + numUI->sprite.getGlobalBounds().width + 48.f, numUI->GetPosition().y);
	
	buttonColUp->SetPosition(numUI->GetPosition().x + 88.f, numUI->GetPosition().y - 54.f);
	buttonColDown->SetPosition(numUI->GetPosition().x + 88.f, numUI->GetPosition().y + 54.f);
	buttonRowUp->SetPosition(numUI->GetPosition().x + 53.f*4, buttonColUp->GetPosition().y);
	buttonRowDown->SetPosition(numUI->GetPosition().x + 212.f, numUI->GetPosition().y + 54.f);

	buttonBack->SetPosition(buttonCreate->GetPosition().x + 100.f, buttonCreate->GetPosition().y);

	//행열 텍스트
	colText->text.setOutlineThickness(1.5f);
	colText->text.setOutlineColor(sf::Color::Black);
	rowText->text.setOutlineThickness(1.5f);
	rowText->text.setOutlineColor(sf::Color::Black);

	colText->SetText(to_string(col), 70, sf::Color::White, Origins::BC, 103, buttonColDown->GetPosition().x, numUI->GetPosition().y - 13.f);
	rowText->SetText(to_string(row), 70, sf::Color::White, Origins::BC, 103, buttonRowDown->GetPosition().x, numUI->GetPosition().y - 13.f);
	
	//팔레트
	tilePallet->SetPosition(numUI->GetPosition().x, 700.f);
	palletLT = tilePallet->GetPosition();
	palletSize = { tilePallet->sprite.getGlobalBounds().width, tilePallet->sprite.getGlobalBounds().height };

	buttonPalL->SetPosition(tilePallet->GetPosition().x, tilePallet->GetPosition().y - 50.f);
	buttonPalR->SetPosition(buttonPalL->GetPosition().x + 80.f, tilePallet->GetPosition().y - 50.f);

	ObjPallet->SetPosition(tilePallet->GetPosition());

	//레이어
	buttonLayer1->SetPosition(numUI->GetPosition().x, 300.f);
	buttonLayer2->SetPosition(buttonLayer1->GetPosition().x + buttonLayer1->sprite.getGlobalBounds().width + 10.f, 300.f);
	buttonLayerObj->SetPosition(buttonLayer1->GetPosition().x, buttonLayer1->GetPosition().y + buttonLayer1->sprite.getGlobalBounds().height + 10.f);
	buttonLayerColl->SetPosition(buttonLayer2->GetPosition().x, buttonLayerObj->GetPosition().y);
	buttonLayerFarm->SetPosition(buttonLayer1->GetPosition().x, buttonLayerObj->GetPosition().y + buttonLayerObj->sprite.getGlobalBounds().height + 10.f);

	stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);
	Layer1->SetText(stringTable->GetUni("LAYER1", Languages::KOR), 50, sf::Color::White, Origins::MC, 101, buttonLayer1->GetPosition().x + buttonLayer1->sprite.getGlobalBounds().width/2, buttonLayer1->GetPosition().y +18.f);
	Layer2->SetText(stringTable->GetUni("LAYER2", Languages::KOR), 50, sf::Color::White, Origins::MC, 101, buttonLayer2->GetPosition().x + buttonLayer2->sprite.getGlobalBounds().width / 2, buttonLayer2->GetPosition().y + 18.f);
	LayerObj->SetText(stringTable->GetUni("LAYER_OBJ", Languages::KOR), 50, sf::Color::White, Origins::MC, 101, buttonLayerObj->GetPosition().x + buttonLayerObj->sprite.getGlobalBounds().width / 2, buttonLayerObj->GetPosition().y + 20.f);
	LayerColl->SetText(stringTable->GetUni("LAYER_COLL", Languages::KOR), 50, sf::Color::White, Origins::MC, 101, buttonLayerColl->GetPosition().x + buttonLayerColl->sprite.getGlobalBounds().width / 2, buttonLayerColl->GetPosition().y + 23.f);
	LayerFarm->SetText(stringTable->GetUni("LAYER_FARM", Languages::KOR), 50, sf::Color::White, Origins::MC, 101, buttonLayerFarm->GetPosition().x + buttonLayerFarm->sprite.getGlobalBounds().width / 2, buttonLayerFarm->GetPosition().y + 23.f);

	//세이브로드
	buttonSave->SetPosition(buttonLayer2->GetPosition().x + buttonLayer2->sprite.getGlobalBounds().width + 30.f
		, buttonLayer2->GetPosition().y + 10.f);
	buttonLoad->SetPosition(buttonSave->GetPosition().x,
		buttonSave->GetPosition().y + buttonSave->sprite.getGlobalBounds().height + 10.f);

	saveText->SetText(stringTable->GetUni("SAVE", Languages::KOR), 45, sf::Color::White, Origins::MC, 102,
		buttonSave->GetPosition().x + buttonSave->sprite.getGlobalBounds().width / 2,
		buttonSave->GetPosition().y + 15);

	loadText->SetText(stringTable->GetUni("LOAD", Languages::KOR), 45, sf::Color::White, Origins::MC, 102,
		buttonLoad->GetPosition().x + buttonLoad->sprite.getGlobalBounds().width / 2,
		buttonLoad->GetPosition().y + 15);
	
	nowLayer->SetText("current layer: " + GetCurrentLayer(), 34, sf::Color::White, Origins::TL, 102,
		palletBg->GetPosition().x + palletBg->vertexArray.getBounds().width + 10, palletBg->GetPosition().y + 10.f);
}

void SceneEditor::Exit()
{
	Scene::Exit();
}

void SceneEditor::Update(float dt)
{
	Scene::Update(dt);

	sf::Vector2f mousePosition = INPUT_MGR.GetMousePos();
	sf::Vector2f worldMousPos = ScreenToWorldPos(mousePosition);
	sf::Vector2f uiMousePos = ScreenToUiPos(mousePosition);

	//cout << mousePosition.x << "," << mousePosition.y << endl;
	//cout << uiMousePos.x << "," << uiMousePos.y << endl;
	
	//맵
	if (worldMousPos.x >= MapLT.x && worldMousPos.x <= MapLT.x + MapSize.x
		&& worldMousPos.y >= MapLT.y && worldMousPos.y <= MapLT.y + MapSize.y 
		&& mousePosition.x > palletBg->GetTileMapSize().x)
	{
		int tileX = static_cast<int>((worldMousPos.x - MapLT.x) / tilesize.x);
		int tileY = static_cast<int>((worldMousPos.y - MapLT.y) / tilesize.y);

		if (!IsCollActive && curTile!=nullptr && !IsFarmActive)
		{
			curTile->SetActive(true);
			curTile->SetPosition({ tileX * tilesize.x + MapLT.x, tileY * tilesize.y + MapLT.y });
		}
		else if(IsCollActive || IsFarmActive)
		{
			selColl->SetActive(true);
			selColl->SetPosition({ tileX * tilesize.x + MapLT.x, tileY * tilesize.y + MapLT.y });
		}
		
		if (INPUT_MGR.GetMouseButton(sf::Mouse::Left))
		{
			if (!IsCollActive && !IsFarmActive)
			{
				sf::IntRect texRect = curTile->sprite.getTextureRect();
				selectMap->ChangeTexRect(tileX, tileY, texRect);
				if (currentLayer == 2 && !IsObjectAdded(tileX, tileY, GetObjType(texRect))) //오브젝트 추가
				{
					AddObject(tileX, tileY, texRect, GetObjType(texRect));
				}
			}
			else if(IsCollActive)
			{
				colliders[tileY * col + tileX]->rectangle.setOutlineColor(sf::Color(255, 0, 0, 255));
				colliders[tileY * col + tileX]->rectangle.setFillColor(sf::Color(255, 0, 0, 70));
			}
			else if (IsFarmActive)
			{
				canFarms[tileY * col + tileX]->rectangle.setOutlineColor(sf::Color(95, 0, 255, 255));
				canFarms[tileY * col + tileX]->rectangle.setFillColor(sf::Color(95, 0, 255, 70));
			}
		}
		if (INPUT_MGR.GetMouseButton(sf::Mouse::Right))
		{
			if (IsCollActive)
			{
				colliders[tileY * col + tileX]->rectangle.setOutlineColor(sf::Color(255, 255, 255, 128));
				colliders[tileY * col + tileX]->rectangle.setFillColor(sf::Color::Transparent);
			}
			else if (IsFarmActive)
			{
				canFarms[tileY * col + tileX]->rectangle.setOutlineColor(sf::Color(255, 255, 255, 128));
				canFarms[tileY * col + tileX]->rectangle.setFillColor(sf::Color::Transparent);
			}
		}
	}
	else
	{
		selColl->SetActive(false);
		if (curTile != nullptr)
		{
			curTile->SetActive(false);
		}
	}

	//팔레트 
	if (uiMousePos.x >= palletLT.x && uiMousePos.x <= palletLT.x + palletSize.x
		&& uiMousePos.y >= palletLT.y && uiMousePos.y <= palletLT.y + palletSize.y)
	{
		selPalTile->SetActive(true);
		int tilePalletX = static_cast<int>((uiMousePos.x - palletLT.x) / palletTileSize.x);
		int tilePalletY = static_cast<int>((uiMousePos.y - palletLT.y) / palletTileSize.y);

		selPalTile->SetPosition({ tilePalletX * palletTileSize.x + palletLT.x, tilePalletY * palletTileSize.y + palletLT.y });

		if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			sf::IntRect textureRect(tilePalletX * texTileSize.x + palletTexSize.x * palNumX, tilePalletY * texTileSize.y + palletTexSize.y * palNumY, texTileSize.x, texTileSize.y);
			curTile->sprite.setTextureRect(textureRect);
		}
	}
	else
	{
		selPalTile->SetActive(false);
	}
	//뱡향키 or wasd로 월드 뷰 이동
	{
		direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
		direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);

		float magnitude = Utils::Magnitude(direction);
		if (magnitude > 1.f)
		{
			direction /= magnitude;
		}

		WVcenterPos += direction * 500.f * dt;
		worldView.setCenter(WVcenterPos);
	}
}

void SceneEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneEditor::ChangePallet()
{
	switch (palNum)
	{
	case 1:
		tilePallet->sprite.setTextureRect(RESOURCE_MGR.GetTextureRect("pallet1"));
		palNumX = 0;
		palNumY = 0;
		break;
	case 2:
		tilePallet->sprite.setTextureRect(RESOURCE_MGR.GetTextureRect("pallet2"));
		palNumX = 1;
		palNumY = 0;
		break;
	case 3:
		tilePallet->sprite.setTextureRect(RESOURCE_MGR.GetTextureRect("pallet3"));
		palNumX = 0;
		palNumY = 1;
		break;
	case 4:
		tilePallet->sprite.setTextureRect(RESOURCE_MGR.GetTextureRect("pallet4"));
		palNumX = 1;
		palNumY = 1;
		break;
	}
}

bool SceneEditor::SaveCollider(const std::string& filePath)
{
	std::ofstream outputFile(filePath);

	if (!outputFile.is_open())
	{
		cout << "ERR: 파일을 열 수 없습니다." << endl;
		return false;
	}

	// 파일 헤더
	outputFile << "cols,rows" << endl;
	outputFile << col << "," << row << endl;

	outputFile << "indexX,indexY" << endl;

	for (int i = 0; i < colliders.size(); ++i)
	{
		auto rect = colliders[i];
		if (rect->rectangle.getFillColor() == sf::Color(255, 0, 0, 70))
		{
			int tileX = static_cast<int>((rect->GetPosition().x - MapLT.x) / tilesize.x);
			int tileY = static_cast<int>((rect->GetPosition().y - MapLT.y) / tilesize.y);
			outputFile << tileX << "," << tileY << endl;
		}
	}

	outputFile.close();
	return true;
}

bool SceneEditor::LoadCollider(const string& filePath)
{
	rapidcsv::Document doc(filePath);

	if (!tempcolliders.empty())
	{
		tempcolliders.clear();
	}
	for (int i = 2; i < doc.GetRowCount(); i++)
	{
		auto rows = doc.GetRow<int>(i);
		tempcolliders.push_back({ rows[0], rows[1] });
	}
	return true;
}

bool SceneEditor::SaveCanFarm(const string& filePath)
{
	std::ofstream outputFile(filePath);

	if (!outputFile.is_open())
	{
		cout << "ERR: 파일을 열 수 없습니다." << endl;
		return false;
	}

	// 파일 헤더
	outputFile << "cols,rows" << endl;
	outputFile << col << "," << row << endl;

	outputFile << "indexX,indexY,CanFarm" << endl;

	for (int i = 0; i < canFarms.size(); ++i)
	{
		auto rect = canFarms[i];
		bool canFarm = true;
		if (rect->rectangle.getFillColor() == sf::Color(95, 0, 255, 70))
		{
			canFarm = false;
		}
		int tileX = static_cast<int>((rect->GetPosition().x - MapLT.x) / tilesize.x);
		int tileY = static_cast<int>((rect->GetPosition().y - MapLT.y) / tilesize.y);
		outputFile << tileX << "," << tileY << "," << canFarm << endl;
	}

	outputFile.close();
	return true;
}

bool SceneEditor::LoadCanFarm(const string& filePath)
{
	rapidcsv::Document doc(filePath);

	if (!tempCanFarm.empty())
	{
		tempCanFarm.clear();
	}
	for (int i = 2; i < doc.GetRowCount(); i++)
	{
		auto rows = doc.GetRow<int>(i);
		tempCanFarm.push_back({ rows[0], rows[1], (bool)rows[2]});
	}
	return true;
}

void SceneEditor::SetColliders()
{
	if (!colliders.empty())
	{
		for (auto rect : colliders)
		{
			RemoveGo(rect);
		}
		colliders.clear();
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			RectangleGo* newRect = new RectangleGo(tilesize);
			newRect->rectangle.setFillColor(sf::Color::Transparent);
			newRect->rectangle.setOutlineThickness(1.f);
			newRect->rectangle.setOutlineColor(sf::Color(255, 255, 255, 128));
			newRect->SetPosition(MapLT.x + j * tilesize.x, MapLT.y + i * tilesize.y);
			AddGo(newRect);
			newRect->SetActive(false);
			colliders.push_back(newRect);
		}
	}
}

void SceneEditor::SetCanFarms()
{
	if (!canFarms.empty())
	{
		for (auto rect : canFarms)
		{
			RemoveGo(rect);
		}
		canFarms.clear();
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			RectangleGo* newRect = new RectangleGo(tilesize);
			newRect->rectangle.setFillColor(sf::Color::Transparent);
			newRect->rectangle.setOutlineThickness(1.f);
			newRect->rectangle.setOutlineColor(sf::Color(255, 255, 255, 128));
			newRect->SetPosition(MapLT.x + j * tilesize.x, MapLT.y + i * tilesize.y);
			AddGo(newRect);
			newRect->SetActive(false);
			canFarms.push_back(newRect);
		}
	}
}

string SceneEditor::GetCurrentLayer()
{
	switch (currentLayer)
	{
	case 0:
		return "Layer 1";
	case 1:
		return "Layer 2";
	case 2:
		return "Layer Object";
	case 3:
		return "Layer Collider";
	case 4:
		return "Layer CanFarm";
		
	default:
		break;
	}
}

ObjType SceneEditor::GetObjType(sf::IntRect rect)
{
	if (rect.top == 0)
	{
		if (rect.left < 64)
		{
			return ObjType::Stone;
		}
		else if (rect.left >= 64 && rect.left < 112)
		{
			return ObjType::Weed;
		}
		else if (rect.left >= 112 && rect.left < 144)
		{
			return ObjType::Timber;
		}
		else if (rect.left >= 144/* && rect.left < 144*/)
		{
			return ObjType::Tree;
		}
	}
	else
	{
		return ObjType::None;
	}
}

void SceneEditor::AddObject(int indexX, int indexY, sf::IntRect rect, ObjType type)
{
	//if ((int)type < 0 || (int)type > 3)
	if(type == ObjType::None)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i].indexX == indexX && objects[i].indexY == indexY)
			{
				objects.erase(objects.begin() + i);
				break;
			}
		}
		return;
	}
	Object obj
	{
		indexX, indexY, (float)rect.left, (float)rect.top, (float)rect.width, (float)rect.height, type
	};
	objects.push_back(obj);
}

bool SceneEditor::SaveObject(const std::string& filePath)
{
	std::ofstream outputFile(filePath);

	if (!outputFile.is_open())
	{
		cout << "ERR: 파일을 열 수 없습니다." << endl;
		return false;
	}

	// 파일 헤더
	outputFile << "cols,rows" << endl;
	outputFile << col << "," << row << endl;

	outputFile << "index,indexX,indexY,left,top,width,height,type" << endl;

	for (int i = 0; i < objects.size(); ++i)
	{
		auto objs = objects[i];
		outputFile << i <<"," << objs.indexX << "," << objs.indexY << "," << objs.left << "," << objs.top << "," <<
			objs.width << "," << objs.height << "," << (int)objs.type << endl;
	}

	outputFile.close();
	return true;
}

bool SceneEditor::LoadObject(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);

	if (!objects.empty())
	{
		objects.clear();
	}
	for (int i = 2; i < doc.GetRowCount(); i++)
	{
		auto rows = doc.GetRow<int>(i);
		objects.push_back({ rows[1], rows[2], (float)rows[3], (float)rows[4], (float)rows[5], (float)rows[6],(ObjType)rows[7] });
	}
	return true;
}

bool SceneEditor::IsObjectAdded(int indexX, int indexY, ObjType type)
{
	{
		for (const Object& obj : objects)
		{
			if (obj.indexX == indexX && obj.indexY == indexY && obj.type == type)
			{
				return true; // 이미 같은 타일에 같은 종류의 오브젝트가 추가된 경우
			}
		}
		return false;
	}
}
	