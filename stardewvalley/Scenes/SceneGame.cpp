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
	{
		testFarmMap = (SpriteGo*)AddGo(new SpriteGo("map/testFarmMap.png", "testFarmMap", "testFarmMap"));
		testFarmMap->sprite.setScale(3.f, 3.f);
		testFarmMap->SetOrigin(Origins::MC);
		testFarmMap->SetPosition(0, 0);
		houseExterior = (SpriteGo*)AddGo(new SpriteGo("map/houses.png", "house", "house"));
		houseExterior->sprite.setScale(4.f, 4.f);
		houseExterior->SetOrigin(Origins::BC);
		houseExterior->SetPosition(473, -785);
		houseExterior->collider.setScale(1.f, 0.3f);
		houseExterior->sortLayer = 1;
		shopExterior = (SpriteGo*)AddGo(new SpriteGo("map/spring_town.ko-KR.png", "shop", "shop"));
		shopExterior->sprite.setScale(4.f, 4.f);
		shopExterior->SetOrigin(Origins::BC);
		shopExterior->SetPosition(-537, -785);
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

	//TEXT
	texMoney = (TextGo*)AddGo(new TextGo("TexMoney", "fonts/SDMiSaeng.ttf")); 
	texMin = (TextGo*)AddGo(new TextGo("TexMin", "fonts/SDMiSaeng.ttf"));
	texHour = (TextGo*)AddGo(new TextGo("TexHour", "fonts/SDMiSaeng.ttf"));
	collon = (TextGo*)AddGo(new TextGo("Collon", "fonts/SDMiSaeng.ttf")); 
	texDay = (TextGo*)AddGo(new TextGo("TexDay", "fonts/SDMiSaeng.ttf"));
	dayday = (TextGo*)AddGo(new TextGo("DayDay", "fonts/SDMiSaeng.ttf")); 
 
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
	// VIEW
	auto size = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = size * 0.5f;
	worldView.setSize(size);
	worldView.setCenter(0, 0);
	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	//ui뷰 변경내용 인벤 포지션 변경부분찾기

	Scene::Enter();


	//quickinven->SetPosition(0.f, 0.f);
	/*auto size = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = size * 0.5f;*/

	walls.push_back(houseExterior->GetCollider()); 
	walls.push_back(shopExterior->GetCollider()); 

	for (int i = 0; i < walls.size(); ++i)
	{
		player2->SetWallBounds(walls[i]); 
	}

	//uiView.setSize(size);
	//uiView.setCenter(centerPos);

	//여기서의 포지션은 동일함
	//inven->SetOrigin(Origins::TL);
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
		hour = 0;
		day += 1;
		arrowSpin = 0;
	}
	if (hour == 2)
	{
		player2->ZeroEnergy();
		hour = 6;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F5))
	{
		hour += 1;
	}
	arrowSpin += dt * 0.2381f;
	timeArrow->SetOrigin(Origins::BC);
	timeArrow->sprite.setRotation(arrowSpin);

	texMoney->SetText(to_string(*player2->GetMoney()), 50, sf::Color::Black, Origins::TL, 101, 1675.f, 195.f);
	
	texHour->SetText(to_string(hour), 50, sf::Color::Black, Origins::TL, 101, 1710.f, 115.f);
	collon->SetText(":", 50, sf::Color::Black, Origins::TL, 101, 1755, 115.f);
	texMin->SetText(to_string(min), 50, sf::Color::Black, Origins::TL, 101, 1770.f, 115.f);

	texDay->SetText(to_string(day), 50, sf::Color::Black, Origins::TL, 101, 1800.f, 12.f);
	dayday->SetText("Day: ", 50, sf::Color::Black, Origins::TR, 101, 1795.f, 12.f);


	
	playerBound = player2->GetCollider(); 
	mapBound = testFarmMap->GetCollider();
	
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

	if (inven->GetEndGame())
	{
		window.close();
	}

	
	std::cout << quickinven->GetPosition().x << " " << quickinven->GetPosition().y << std::endl;
	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
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