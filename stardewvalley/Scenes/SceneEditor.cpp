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

SceneEditor::SceneEditor()
	:Scene(SceneId::Editor)
{
	resourceListPath = "scripts/defaultResourceList.csv";
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
		cout << "OnClick" << endl;
		if (farmMap != nullptr)
		{
			RemoveGo(farmMap);
			delete farmMap;
			farmMap = nullptr;
		}
		
		farmMap = (TileMap*)AddGo(new TileMap("map/spring_outdoorsTileSheet_cut.png", "dirtTile"));
		farmMap->Reset();
		farmMap->Load(col, row, 48.f, 0.f);
		farmMap->SetOrigin(Origins::MC);
		farmMap->SetPosition(centerPos.x + 500.f, centerPos.y);

		MapLT = { farmMap->vertexArray.getBounds().left, farmMap->vertexArray.getBounds().top };
		MapSize = farmMap->GetTileMapSize();
		farmMap->sortLayer = -1;

		//worldView.setCenter(farmMap->GetPosition());

		//cout << MapLT.x << ", " << MapLT.y << endl;
	};

	buttonColUp = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowUp", "arrowUp"));
	buttonColUp->SetOrigin(Origins::BC);
	buttonColUp->sortLayer = 101;
	buttonColUp->OnClick = [this]()
	{
		col++;
		colText->SetString(to_string(col));
	};

	buttonColDown = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowDown", "arrowDown"));
	buttonColDown->SetOrigin(Origins::TC);
	buttonColDown->sortLayer = 101;
	buttonColDown->OnClick = [this]()
	{
		col--;
		colText->SetString(to_string(col));
	};
	
	buttonRowUp = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowUp", "arrowUp"));
	buttonRowUp->SetOrigin(Origins::BC);
	buttonRowUp->sortLayer = 101;
	buttonRowUp->OnClick = [this]()
	{
		row++;
		rowText->SetString(to_string(row));
	};

	buttonRowDown = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowDown", "arrowDown"));
	buttonRowDown->SetOrigin(Origins::TC);
	buttonRowDown->sortLayer = 101;
	buttonRowDown->OnClick = [this]()
	{
		row++;
		rowText->SetString(to_string(row));
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
	selectTile->SetScale({ 3.f, 3.f });
	selectTile->SetOrigin(Origins::TL);
	sf::IntRect texRect(0, 0, 16, 16);
 	selectTile->sprite.setTextureRect(texRect);
	selectTile->SetActive(false);
	selectTile->sortLayer = 3;

	/*----타일 팔레트----*/
	tilePallet = (SpriteGo*)AddGo(new SpriteGo("map/spring_outdoorsTileSheet_cut.png", "tilePallet"));
	tilePallet->SetOrigin(Origins::TL);
	tilePallet->sortLayer = 101;
	tilePallet->SetScale({ 3.f, 3.f });
	tilePallet->sprite.setTextureRect(RESOURCE_MGR.GetTextureRect("pallet1"));

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

	/*---행열 조절---*/
	//버튼ui
	numUI->SetPosition(48.f, 72.f + numUI->sprite.getGlobalBounds().height / 2);

	buttonCreate->SetPosition(numUI->GetPosition().x + numUI->sprite.getGlobalBounds().width + 48.f, numUI->GetPosition().y);
	
	buttonColUp->SetPosition(numUI->GetPosition().x + 88.f, numUI->GetPosition().y - 54.f);
	buttonColDown->SetPosition(numUI->GetPosition().x + 88.f, numUI->GetPosition().y + 54.f);
	buttonRowUp->SetPosition(numUI->GetPosition().x + 53.f*4, buttonColUp->GetPosition().y);
	buttonRowDown->SetPosition(numUI->GetPosition().x + 212.f, numUI->GetPosition().y + 54.f);

	//행열 텍스트
	colText->text.setOutlineThickness(1.5f);
	colText->text.setOutlineColor(sf::Color::Black);
	rowText->text.setOutlineThickness(1.5f);
	rowText->text.setOutlineColor(sf::Color::Black);

	colText->SetText(to_string(col), 70, sf::Color::White, Origins::BC, 103, buttonColDown->GetPosition().x, numUI->GetPosition().y - 18.f);
	rowText->SetText(to_string(col), 70, sf::Color::White, Origins::BC, 103, buttonRowDown->GetPosition().x, numUI->GetPosition().y - 18.f);
	
	//팔레트
	tilePallet->SetPosition(numUI->GetPosition().x, 600.f);
	palletLT = tilePallet->GetPosition();
	palletSize = { tilePallet->sprite.getGlobalBounds().width, tilePallet->sprite.getGlobalBounds().height };

	buttonPalL->SetPosition(tilePallet->GetPosition().x, tilePallet->GetPosition().y - 50.f);
	buttonPalR->SetPosition(buttonPalL->GetPosition().x + 80.f, tilePallet->GetPosition().y - 50.f);

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
		&& worldMousPos.y >= MapLT.y && worldMousPos.y <= MapLT.y + MapSize.y)
	{
		selectTile->SetActive(true);
		int tileX = static_cast<int>((worldMousPos.x - MapLT.x) / tilesize.x);
		int tileY = static_cast<int>((worldMousPos.y - MapLT.y) / tilesize.y);

		selectTile->SetPosition({ tileX * tilesize.x + MapLT.x, tileY * tilesize.y + MapLT.y });
		sf::IntRect texRect = selectTile->sprite.getTextureRect();
		if (INPUT_MGR.GetMouseButton(sf::Mouse::Left))
		{
			farmMap->ChangeTexRect(tileX, tileY, texRect);
		}
	}
	else
	{
		selectTile->SetActive(false);
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
			selectTile->sprite.setTextureRect(textureRect);
		}

	}
	else
	{
		selPalTile->SetActive(false);
	}
	//230810, 윤유림, 마우스로 월드 뷰 이동
	{
		direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
		direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);

		float magnitude = Utils::Magnitude(direction);
		if (magnitude > 1.f)
		{
			direction /= magnitude;
		}

		WVcenterPos += direction * 300.f * dt;
		worldView.setCenter(WVcenterPos);
	}
	//

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
	