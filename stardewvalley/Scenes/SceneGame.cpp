#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include "Player.h"
#include "Framework.h"
#include "Ground.h"
#include "VertexArrayGo.h"
#include "Player2.h"
#include "UiButton.h"
#include "Wall.h"
#include "Axe.h"
#include <sstream>
#include "TextGo.h"
#include "SliceImageGo.h"
#include "Inventory.h"
#include "RootingItem.h"
#include "DataTableMgr.h"
#include "AllItemTable.h"
#include "QuickInventory.h"
#include "RectangleGo.h"
#include "ShopTap.h"
#include "ShopInterior.h"
#include "TileMap.h"
#include "rapidcsv.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "scripts/defaultResourceList.csv";
}

void SceneGame::Init()
{
	Release();

	// VIEW
	auto size = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = size * 0.5f;
	worldView.setSize(size);
	worldView.setCenter(0, 0);
	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);

	// TEST MAP
	{	//0818 맵툴 맵 적용
		/*testFarmMap = (SpriteGo*)AddGo(new SpriteGo("map/testFarmMap.png", "testFarmMap", "testFarmMap"));
		testFarmMap->sprite.setScale(3.f, 3.f);
		testFarmMap->SetOrigin(Origins::MC);
		testFarmMap->SetPosition(0, 0);*/

		testFarmMap = (TileMap*)AddGo(new TileMap("map/spring_outdoorsTileSheet_cut.png", "MapTile1"));
		testFarmMap->Reset();
		testFarmMap->Load("tables/newMapLayer1.csv");
		testFarmMap->SetOrigin(Origins::MC);

		testFarmMap2 = (TileMap*)AddGo(new TileMap("map/spring_outdoorsTileSheet_cut.png", "MapTile2"));
		testFarmMap2->Reset();
		testFarmMap2->Load("tables/newMapLayer2.csv"); //투명한 타일 176, 0
		testFarmMap2->SetOrigin(Origins::MC);

		testFarmMapObj = (TileMap*)AddGo(new TileMap("map/object.png", "MapObj"));
		testFarmMapObj->Reset();
		testFarmMapObj->Load("tables/newMapLayerObj.csv"); //투명한 타일 96, 16
		testFarmMapObj->SetOrigin(Origins::MC);

		houseExterior = (SpriteGo*)AddGo(new SpriteGo("map/houses.png", "house", "house"));
		houseExterior->sprite.setScale(4.f, 4.f);
		houseExterior->SetOrigin(Origins::BC);
		//houseExterior->SetPosition(473, -785);
		houseExterior->collider.setScale(1.f, 0.3f);
		houseExterior->sortLayer = 1;

		shopExterior = (SpriteGo*)AddGo(new SpriteGo("map/spring_town.ko-KR.png", "shop", "shop"));
		shopExterior->sprite.setScale(4.f, 4.f);
		shopExterior->SetOrigin(Origins::BC);
		//shopExterior->SetPosition(-537, -785);
		shopExterior->collider.setScale(1.f, 0.3f);
	}
	
	// PLAYER
	{
		player2 = (Player2*)AddGo(new Player2());
		player2->SetOrigin(Origins::BC);
		player2->sortLayer = 2;
		player2->collider.setScale(0.5f, 0.1f);
		player2->SetRootingItems(&rootingItems);
	}

	// INVEN
	{
		inven = (Inventory*)AddGo(new Inventory("inven"));
		inven->sortLayer = 100;
		inven->SetPosition(windowSize / 2.f);
		inven->SetPlayer(player2);
		player2->SetInventory(inven);
		quickinven = (QuickInventory*)AddGo(new QuickInventory("quickinven"));
		quickinven->sortLayer = 101;
		quickinven->SetPosition(windowSize.x * 0.5f, windowSize.y - 200.f);
		quickinven->SetPlayer(player2);
	}

	// INGAME UI
	{
		energy = (SpriteGo*)AddGo(new SpriteGo("graphics/Cursors.ko-KR.png", "Energy", "Energy"));
		energy->SetOrigin(Origins::BR);
		energy->SetPosition(size);
		energy->SetScale(4.5f, 4.5f);
		energy->sortLayer = 100;

		info = (SpriteGo*)AddGo(new SpriteGo("graphics/Cursors.ko-KR.png", "Info", "Info"));
		info->SetOrigin(Origins::TR);
		info->SetScale(4.5f, 4.5f);
		info->SetPosition(size.x, 0);
		info->sortLayer = 100;

		timeArrow = (SpriteGo*)AddGo(new SpriteGo("graphics/Cursors.ko-KR.png", "TimeArrow", "TimeArrow"));
		timeArrow->SetScale(4.5f, -4.5f);
		timeArrow->SetOrigin(Origins::TC);
		timeArrow->collider.setScale(1.f, -1.f);
		timeArrow->SetPosition(info->GetPosition().x - 225.f, info->GetPosition().y + 93.f);
		timeArrow->sortLayer = 100;

		sf::Vector2f recsize(26.f, 1.f);
		energyBar = (RectangleGo*)AddGo(new RectangleGo(recsize)); 
		//energyBar.SetSize(sf::Vector2f(26.f, 1.f));  
		energyBar->SetOrigin(Origins::BC);;
		energyBar->SetPosition(energy->GetPosition());
		energyBar->SetColor(sf::Color::Green);
		energyBar->sortLayer = 100;

		quickinven->SetQuickSlot(inven->GetSlot());
	}

	// SHOP
	{
		shopInterior = (ShopInterior*)AddGo(new ShopInterior("shopInterior"));
		shopInterior->SetPosition(0, 0);
		shopInterior->SetActive(false);

		shopTap = (ShopTap*)AddGo(new ShopTap("shop"));
		shopTap->SetPlayer(player2);
		shopTap->SetInventory(inven);
		shopTap->SetActive(false);
		shopTap->sortLayer = 101;
	}

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneGame::Enter()
{
	Scene::Enter();
	auto size = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = size * 0.5f;
	//walls.push_back(shopCounter1->GetCollider()); 
	//walls.push_back(shopMid1->GetCollider()); 
	//walls.push_back(shopMid2_1->GetCollider()); 
	//walls.push_back(shopMid2_2->GetCollider()); 
	//walls.push_back(shopMid3_1->GetCollider()); 
	//walls.push_back(shopMid3_2->GetCollider()); 
	//walls.push_back(shopBox->GetCollider()); 

	//for (int i = 0; i < shopWalls->Walls.size(); ++i)
	//{
	//	walls.push_back(shopWalls->Walls[i].getGlobalBounds());
	//}
	
	font.loadFromFile("fonts/SDMiSaeng.ttf");
	textMoney.setFont(font);
	textMin.setFont(font);
	textHour.setFont(font);
	textDay.setFont(font);

	// ������, 230811, uiview�� Init���� �ִ� ���� �� ���� ����. �ּ�ó��
	//uiView.setSize(size);
	//uiView.setCenter(centerPos);

	// �����, 230807, �׽�Ʈ�� �ּ�ó��
	//player2->SetOrigin(Origins::MC);
	//player2->SetPosition(centerPos);
	//
	uiView.setSize(size);
	uiView.setCenter(centerPos);

	testFarmMap->SetPosition(0, 0);
	testFarmMap2->SetPosition(testFarmMap->GetPosition());
	testFarmMapObj->SetPosition(testFarmMap->GetPosition());

	tileSize = testFarmMap->GetTileSize();
	
	sf::Vector2f mapLT = { testFarmMap->vertexArray.getBounds().left, testFarmMap->vertexArray.getBounds().top };
	houseExterior->SetPosition(mapLT.x + tileSize.x * housePos.x, mapLT.y + tileSize.y * housePos.y);
	walls.push_back(houseExterior->GetCollider());

	shopExterior->SetPosition(mapLT.x + tileSize.x * shopPos.x, mapLT.y + tileSize.y * shopPos.y);
	walls.push_back(shopExterior->GetCollider());

	rapidcsv::Document doc("tables/newMapCollider.csv");

	for (int i = 2; i < doc.GetRowCount(); i++)
	{
		auto rows = doc.GetRow<int>(i);
		sf::FloatRect rect = { mapLT.x + rows[0] * tileSize.x, mapLT.y + rows[1] * tileSize.y, tileSize.x, tileSize.y };
		walls.push_back(rect);
	}

	for (int i = 0; i < walls.size(); ++i)
	{
		player2->SetWallBounds(walls[i]);
	}
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	player2->SetItemId(quickinven->GetItemId()); 
	time +=dt;
	if (time >= 7.f)
	{
		min += 10;
		time = 0.f;
	}
	if (min == 60)
	{
		min = 0;
		hour += 1;
	}
	if (hour == 24)
	{
		hour = 6;
		day += 1;
		arrowSpin = 0;
	}
	
	arrowSpin += dt * 0.2381f;
	timeArrow->SetOrigin(Origins::BC);
	timeArrow->sprite.setRotation(arrowSpin);

	std::stringstream ss; 
	ss << *player2->GetMoney();
	textMoney.setString(ss.str());
	textMoney.setCharacterSize(50);
	textMoney.setPosition(1675.f, 195.f);
	textMoney.setFillColor(sf::Color::Black);

	std::stringstream sss;
	sss << hour << ":" << min; 
	textHour.setString(sss.str()); 
	textHour.setCharacterSize(50); 
	textHour.setPosition(1710.f, 115.f); 
	textHour.setFillColor(sf::Color::Black); 

	std::stringstream ssss; 
	ssss << day << "Day"; 
	textDay.setString(ssss.str());
	textDay.setCharacterSize(50);
	textDay.setPosition(1775.f, 12.f);
	textDay.setFillColor(sf::Color::Black);

	
	playerBound = player2->GetCollider(); 
	mapBound = testFarmMap->vertexArray.getBounds();
	
	player2->SetCollider(playerBound);

	energyBar->SetSize(sf::Vector2f(26.f, player2->GetEnergy() * 0.67));
	energyBar->SetPosition(energy->GetPosition().x- 26.f,energy->GetPosition().y - 10.f);
	energyBar->SetOrigin(Origins::BC);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Q))
	{
		if (enterShop)
		{
			enterShop = false;
			for (auto go : gameObjects)
			{
				if (go->GetActive())
				{
					go->SetActive(false);
				}
				else
				{
					go->SetActive(true);
				}
			}
			player2->SetActive(true);
			player2->SetPosition(-463.f, -770.f); 
			energy->SetActive(true);
			info->SetActive(true);
			timeArrow->SetActive(true);
			inven->SetActive(true);
			quickinven->SetActive(true);
			energyBar->SetActive(true);
		}
		else
		{
			enterShop = true;
			for (auto go : gameObjects)
			{
				if (go->GetActive())
				{
					go->SetActive(false);
					
				}
				else
				{
					go->SetActive(true);
				}
			}

			player2->SetActive(true);	
			player2->SetPosition(419.f, 1866.f); 
			energy->SetActive(true);
			info->SetActive(true);
			timeArrow->SetActive(true); 
			inven->SetActive(true);
			quickinven->SetActive(true);
			energyBar->SetActive(true); 
		}
	}
	
	worldView.setCenter(player2->GetPosition());

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneId::Editor);
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num0))
	{
		SpawnRootingItem(ItemId::branch);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num9))
	{
		SpawnRootingItem(ItemId::coal);
	}

	
	if (inven->GetInvenOff())
	{
		quickinven->SetActive(false);
	}
	else if (!inven->GetInvenOff())
	{
		quickinven->SetActive(true);
	}
	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(textMoney);
	window.draw(textHour);
	window.draw(textDay);
}

void SceneGame::SpawnRootingItem(ItemId id)
{
	const ItemInfo* info = DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem)->Get(id);
	rootingItems.push_back((RootingItem*)AddGo(new RootingItem(info->itemId, info->resource, info->name_e, info->nickName)));
	for (auto r : rootingItems)
	{
		r->Reset();
	}
}

VertexArrayGo* SceneGame::CreateBackGround(sf::Vector2i size, sf::Vector2f tileSize, sf::Vector2f texSize, string textureId)
{
	VertexArrayGo* background = new VertexArrayGo(textureId, "Background");
	background->vertexArray.setPrimitiveType(sf::Quads);
	background->vertexArray.resize(size.x * size.y * 4); 

	sf::Vector2f startPos = { 0, 0 }; 
	sf::Vector2f offsets[4] =
	{
		{0.f, 0.f},
		{tileSize.x, 0.f},
		{tileSize.x, tileSize.y},
		{0.f, tileSize.y}
	}; 
	sf::Vector2f texOffsets[4] =
	{
		{0.f, 0.f},
		{texSize.x, 0.f},
		{texSize.x, texSize.y},
		{0.f, texSize.y}
	};

	sf::Vector2f currPos = startPos;
	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			int texIndex = 3;
			if (i != 0 && i != size.y - 1 && j != 0 && j != size.x - 1)
				
			{
				texIndex = Utils::RandomRange(0, 3); 
			}

			int tileIndex = size.x * i + j; 
			for (int k = 0; k < 4; k++) 
			{
				int vertexIndex = tileIndex * 4 + k;
				background->vertexArray[vertexIndex].position = currPos + offsets[k];
				background->vertexArray[vertexIndex].texCoords = texOffsets[k];
				background->vertexArray[vertexIndex].texCoords.y += texSize.y * texIndex;
			}
			currPos.x += tileSize.x;
		}
		currPos.x = startPos.x;
		currPos.y += tileSize.y;
	}
	return background;
}