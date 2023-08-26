#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "SpriteGo.h"
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
#include "HomeInterior.h"
#include "HomeTap.h"
#include "Stone.h"
#include "Timber.h"
#include "Weed.h"
#include "Tree.h"
#include "HoeDirt.h"
#include "SceneTitle.h"
#include "Parsnip.h"
#include "Crop.h"
#include "Cauliflower.h"
#include "Potato.h"
#include "EffectGo.h"
#include "SaveLoadData.h"
#include "Slot.h"
#include "StringTable.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	//resourceListPath = "scripts/defaultResourceList.csv";
}

void SceneGame::Init()
{
	Release();
	auto size = FRAMEWORK.GetWindowSize();
	// VIEW
	sf::Vector2f centerPos = size * 0.5f;
	// PLAYER
	{
		player2 = (Player2*)AddGo(new Player2());
		player2->SetOrigin(Origins::BC);
		player2->sortLayer = 1; 
		player2->sortOrder = 100;
		player2->collider.setScale(1.f, 1.f);
		player2->SetRootingItems(&rootingItems);
	}

	// INVEN
	{
		inven = (Inventory*)AddGo(new Inventory("inven"));
		inven->sortLayer = 150;
		inven->SetPosition(windowSize / 2.f);
		inven->SetPlayer(player2);
		player2->SetInventory(inven);

		quickinven = (QuickInventory*)AddGo(new QuickInventory("quickinven"));
		quickinven->sortLayer = 150;
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
		shopTap->sortLayer = 101;
		shopTap->SetPlayer(player2);
		shopTap->SetInventory(inven);
		shopTap->SetPierre(shopInterior->GetPierre());
		shopTap->SetActive(false);
	}

	// HOME
	{
		homeInterior = (HomeInterior*)AddGo(new HomeInterior("homeInterior"));
		homeInterior->SetPosition(0, 0);
		homeInterior->SetActive(false);

		bedding = (SpriteGo*)AddGo(new SpriteGo("map/bedding.png", "bedding"));
		bedding->SetOrigin(Origins::TL);
		bedding->SetPosition(544.f, 551.f);
		bedding->sortLayer = 3;
		bedding->SetActive(false);

		homeTap = (HomeTap*)AddGo(new HomeTap("homeTap"));
		homeTap->sortLayer = 100;
		homeTap->SetBedding(bedding);
		homeTap->SetPlayer(player2);
	}

	//TEXT
	{
		texMoney = (TextGo*)AddGo(new TextGo("TexMoney", "fonts/SDMiSaeng.ttf"));
		texMin = (TextGo*)AddGo(new TextGo("TexMin", "fonts/SDMiSaeng.ttf"));
		texHour = (TextGo*)AddGo(new TextGo("TexHour", "fonts/SDMiSaeng.ttf"));
		collon = (TextGo*)AddGo(new TextGo("Collon", "fonts/SDMiSaeng.ttf"));
		texDay = (TextGo*)AddGo(new TextGo("TexDay", "fonts/SDMiSaeng.ttf"));
		dayday = (TextGo*)AddGo(new TextGo("DayDay", "fonts/SDMiSaeng.ttf"));

		//test
		sf::Vector2f rectsize = { 72.f,72.f };
		//testbox = (RectangleGo*)AddGo(new RectangleGo(rectsize)); 
		//testbox->sortLayer = 3;
		//testbox->SetColor(sf::Color(0,0,255,100));

		/*rectsize = { 1980.f,1080.f };
		night = (RectangleGo*)AddGo(new RectangleGo(rectsize));
		night->sortLayer = 3;
		night->SetColor(sf::Color(0, 0, 128, 200));*/
	}
	
	//FARMING
	{
		selectTile = (SpriteGo*)AddGo(new SpriteGo("graphics/Cursors.ko-KR.png", "greenTile", "greenTile"));
		selectTile->SetScale({ 4.5f, 4.5f });
		selectTile->SetOrigin(Origins::TL);
		selectTile->SetActive(false);
		selectTile->sortLayer = 2;
		selectTile->sortOrder = 0;
	}

	//SET CROP POOL
	{
		parsnipPool.OnCreate = [this](Parsnip* parsnip)
		{
			parsnip->sortLayer = 1;
			parsnip->SetType(CropId::Parsnip);
			parsnip->SetPool(&parsnipPool);
		};
		parsnipPool.Init();

		potatoPool.OnCreate = [this](Potato* potato)
		{
			potato->sortLayer = 1;
			potato->SetType(CropId::Potato);
			potato->SetPool(&potatoPool);
		};
		potatoPool.Init();

		cauliflowerPool.OnCreate = [this](Cauliflower* cauli)
		{
			cauli->sortLayer = 1;
			cauli->SetType(CropId::Cauliflower);
			cauli->SetPool(&cauliflowerPool);
		};
		cauliflowerPool.Init();
	}

	// FADE
	sf::Vector2f recsize = { (float)window.getSize().x, (float)window.getSize().y };
	fadeRectangle = (RectangleGo*)AddGo(new RectangleGo(recsize));
	fadeRectangle->rectangle.setFillColor(sf::Color::Black);
	fadeRectangle->sortLayer = 100;
	fadeRectangle->sortOrder = -1;

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	parsnipPool.Release();
	potatoPool.Release();
	cauliflowerPool.Release();

	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneGame::Enter()
{
	// TEST MAP
	{	//0818 맵툴 맵 적용]
		//땅
		testFarmMap = (TileMap*)AddGo(new TileMap("map/spring_outdoorsTileSheet_cut.png", "MapTile1"));
		testFarmMap->Reset();
		testFarmMap->Load("tables/newMapLayer1.csv");
		testFarmMap->SetOrigin(Origins::MC);
		testFarmMap->sortLayer = 0;
		testFarmMap->sortOrder = 0;
		col = testFarmMap->GetSize().x;
		row = testFarmMap->GetSize().y;
		

		//울타리나 절벽
		testFarmMap2 = (TileMap*)AddGo(new TileMap("map/spring_outdoorsTileSheet_cut.png", "MapTile2"));
		testFarmMap2->Reset();
		testFarmMap2->Load("tables/newMapLayer2.csv"); //투명한 타일 176, 0
		testFarmMap2->SetOrigin(Origins::MC);
		testFarmMap2->sortLayer = 0;
		testFarmMap2->sortOrder = 1;

		houseExterior = (SpriteGo*)AddGo(new SpriteGo("map/houses.png", "house", "house"));
		houseExterior->sprite.setScale(4.f, 4.f);
		houseExterior->SetOrigin(Origins::BC);
		houseExterior->collider.setScale(1.f, 0.3f);
		houseExterior->sortLayer = 1;
		houseExterior->sortOrder = housePos.y - 2;

		shopExterior = (SpriteGo*)AddGo(new SpriteGo("map/spring_town.ko-KR.png", "shop", "shop"));
		shopExterior->sprite.setScale(4.f, 4.f);
		shopExterior->SetOrigin(Origins::BC);
		shopExterior->sortLayer = 1;
		shopExterior->sortOrder = shopPos.y - 1;
		shopExterior->collider.setScale(1.f, 0.3f);
	}

	//HOE DIRT
	{
		dirtArray.resize(row);
		for (int i = 0; i < row; i++)
		{
			dirtArray[i].resize(col);
		}

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				dirt = (HoeDirt*)AddGo(new HoeDirt("hoedirt", "map/hoeDirt.png", "dirt", "waterdirt"));
				dirt->sortLayer = 0;
				dirt->sortOrder = 2;
				dirt->SetIndex(j, i);
				dirt->SetActive(false);
				dirtArray[i][j] = dirt;
			}
		}
	}

	// VIEW
	{
		auto size = FRAMEWORK.GetWindowSize();
		sf::Vector2f centerPos = size * 0.5f;

		worldView.setSize(size);
		worldView.setCenter(0, 0);

		uiView.setSize(size);
		uiView.setCenter(size * 0.5f);
	}

	stoneCount = 0;
	timberCount = 0;
	weedCount = 0;
	treeCount = 0;

	// FILE LOAD & NEW GAME
	{
		if (dynamic_cast<SceneTitle*>(SCENE_MGR.GetTitleScene())->loadData)
		{
			FileLoad(true);
			dynamic_cast<SceneTitle*>(SCENE_MGR.GetTitleScene())->loadData = false;
		}
		else
		{
			FileLoad(false);
		}
	}

	// OBJECT SET MAP LT & SET SORT ORDER
	{
		tileSize = testFarmMap->GetTileSize();
		mapSize = testFarmMap->GetTileMapSize();
		mapLT = { testFarmMap->vertexArray.getBounds().left, testFarmMap->vertexArray.getBounds().top };

		for (int i = 0; i < stones.size(); i++)
		{
			stones[i]->SetMapLT(mapLT);
			stones[i]->sortOrder = stones[i]->GetIndex().y;
		}
		for (int i = 0; i < timbers.size(); i++)
		{
			timbers[i]->SetMapLT(mapLT);
			timbers[i]->sortOrder = timbers[i]->GetIndex().y;
		}
		for (int i = 0; i < weeds.size(); i++)
		{
			weeds[i]->SetMapLT(mapLT);
			weeds[i]->sortOrder = weeds[i]->GetIndex().y;
		}
		for (int i = 0; i < trees.size(); i++)
		{
			trees[i]->stump->SetMapLT(mapLT);
			trees[i]->sortOrder = trees[i]->stump->GetIndex().y;
		}
		for (auto i : parsnipPool.GetUseList())
		{
			i->SetPosition({ i->GetIndex().x * tileSize.x + mapLT.x, i->GetIndex().y * tileSize.y + mapLT.y});
		}
		for (auto i : potatoPool.GetUseList())
		{
			i->SetPosition({ i->GetIndex().x * tileSize.x + mapLT.x, i->GetIndex().y * tileSize.y + mapLT.y});
		}
		for (auto i : cauliflowerPool.GetUseList())
		{
			i->SetPosition({ i->GetIndex().x * tileSize.x + mapLT.x, i->GetIndex().y * tileSize.y + mapLT.y});
		}
	}

	// DIRT POSITION SETTING
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				dirtArray[i][j]->SetPosition(mapLT.x + tileSize.x * j, mapLT.y + tileSize.y * i);
			}
		}
	}
	
	// SHOP, HOUSE
	{
		// SHOP
		{
			shopExterior->SetPosition(mapLT.x + tileSize.x * shopPos.x, mapLT.y + tileSize.y * shopPos.y);
			shopInterior->SetActive(false);
			shopTap->SetActive(false);
			shopTap->SetPierre(shopInterior->GetPierre());
		}
		// HOME
		{
			houseExterior->SetPosition(mapLT.x + tileSize.x * housePos.x, mapLT.y + tileSize.y * housePos.y);
			houseExterior->colliderOnOff = false;
			homeInterior->SetActive(false);
			bedding->SetActive(false);
		}
	}

	Scene::Enter();

	// PLAYER COLLIDER SETTING
	{
		//walls.push_back(shopExterior->GetCollider());
		farmWalls.push_back(shopExterior->GetCollider());
	}

	// SET SHOP COLLIDER
	{
		for (auto coll : shopInterior->GetshopInteriors())
		{
			shopWalls.push_back(coll.GetCollider());
		}
		for (auto wall : shopInterior->GetWall().Walls)
		{
			shopWalls.push_back(wall.rect.getGlobalBounds());
			if (wall.wallType == Wall::Types::Shop_B3)
			{
				shopExit = wall.rect;
			}
		}
	}

	// SET HOME COLLIDER
	{
		for (auto wall : homeInterior->GetWall().Walls)
		{
			houseWalls.push_back(wall.rect.getGlobalBounds());
			if (wall.wallType == Wall::Types::Home_B3)
			{
				homeExit = wall.rect;
			}
		}
	}

	// MAP COLLIDER SETTING
	{
		rapidcsv::Document doc("tables/newMapCollider.csv");
		for (int i = 2; i < doc.GetRowCount(); i++)
		{
			auto rows = doc.GetRow<int>(i);
			sf::FloatRect rect = { mapLT.x + rows[0] * tileSize.x, mapLT.y + rows[1] * tileSize.y, tileSize.x, tileSize.y };
			//walls.push_back(rect);
			farmWalls.push_back(rect);
		}
		for (int i = 0; i < stoneCount; i++)
		{
			Stone* stone = (Stone*)FindGo("stone" + to_string(i));
			//walls.push_back(stone->GetCollider());
			farmWalls.push_back(stone->GetCollider());
		}
		for (int i = 0; i < timberCount; ++i)
		{
			Timber* timber = (Timber*)FindGo("timber" + to_string(i));
			//walls.push_back(timber->GetCollider());
			farmWalls.push_back(timber->GetCollider());
		}
		for (int i = 0; i < weedCount; ++i)
		{
			Weed* weed = (Weed*)FindGo("weed" + to_string(i));
			//walls.push_back(weed->GetCollider());
			farmWalls.push_back(weed->GetCollider());
		}
		for (int i = 0; i < treeCount; ++i)
		{
			Tree* tree = (Tree*)FindGo("tree" + to_string(i));
			//walls.push_back(tree->stump->GetCollider());
			farmWalls.push_back(tree->stump->GetCollider());
		}
		for (int i = 0; i < houseWalls.size(); ++i)
		{
			//player2->SetWallBounds(walls[i]);
			player2->SetWallBounds(houseWalls[i]);
		}
	}
	
	// INIT SETTING
	{
		for (auto go : gameObjects)
		{
			if (go->GetActive())
			{
				go->SetActive(false);
			}
		}
		SetAct(true);
		shopTap->SetActive(true); // 내부에서 active 관리
		homeTap->SetActive(true); // 내부에서 active 관리
		homeInterior->SetActive(true);
		bedding->SetActive(true);
		quickinven->SetActive(true);
		location = Location::Home;
		player2->SetPosition(playerSpwan);
		init = false;
	}

	//FADE
	fadeRectangle->SetOrigin(Origins::MC);
	fadeRectangle->SetPosition(uiView.getCenter());
}

void SceneGame::Exit()
{
	ClearObjectPool(parsnipPool);
	ClearObjectPool(potatoPool);
	ClearObjectPool(cauliflowerPool);

	for (auto i : rootingItems)
	{
		RemoveGo(i);
	}
	rootingItems.clear();

	ClearMapObj(stones);
	ClearMapObj(timbers);
	ClearMapObj(weeds);
	ClearMapObj(trees);

	Scene::Exit();
}

void SceneGame::Update(float dt)
{

	sf::Vector2f mousePosition = INPUT_MGR.GetMousePos();
	sf::Vector2f worldMousPos = ScreenToWorldPos(mousePosition);

	int mouseTileX = static_cast<int>((worldMousPos.x - mapLT.x) / tileSize.x); 
	int mouseTileY = static_cast<int>((worldMousPos.y - mapLT.y) / tileSize.y); 

	// PLAYER TILE
	int playerTileX = static_cast<int>((player2->GetPosition().x - mapLT.x) / tileSize.x); 
	int playerTileY = static_cast<int>((player2->GetPosition().y - mapLT.y) / tileSize.y); 

	if (abs(mouseTileX - playerTileX) < 2 && abs(mouseTileY - playerTileY) < 2)
	{
		// HARVEST CROP
		{
			if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) || INPUT_MGR.GetMouseButtonDown(sf::Mouse::Right))
			{

				if (dirtArray[mouseTileY][mouseTileX]->GetIsPlanted())
				{
					CropId id = dirtArray[mouseTileY][mouseTileX]->GetCropId();
					switch (id)
					{
					case CropId::Parsnip:
						HarvestParsnip(mouseTileX, mouseTileY);
						break;
					case CropId::Potato:
						HarvestPotato(mouseTileX, mouseTileY);
						break;
					case CropId::Cauliflower:
						HarvestCauli(mouseTileX, mouseTileY);
						break;
					default:
						break;
					}
				}
			}
		}
	}

	Scene::Update(dt);

	// TREE TRANSPARENT
	{
		for (auto tree : trees)
		{
			sf::FloatRect intersection;
			if (tree->GetHitbox().getGlobalBounds().intersects(player2->GetCollider(), intersection))
			{
				if (intersection.width >= player2->GetCollider().width)
				{
					tree->branch.setColor(sf::Color(255, 255, 255, 150));
				}
			}
			else
			{
				tree->branch.setColor(sf::Color(255, 255, 255, 255));
			}
		}
	}

	// MOUSE POS
	/*sf::Vector2f mousePosition = INPUT_MGR.GetMousePos();
	sf::Vector2f worldMousPos = ScreenToWorldPos(mousePosition);*/

	// MOUSE TILE
	//int mouseTileX = static_cast<int>((worldMousPos.x - mapLT.x) / tileSize.x);
	//int mouseTileY = static_cast<int>((worldMousPos.y - mapLT.y) / tileSize.y);

	//// PLAYER TILE
	//int playerTileX = static_cast<int>((player2->GetPosition().x - mapLT.x) / tileSize.x);
	//int playerTileY = static_cast<int>((player2->GetPosition().y - mapLT.y) / tileSize.y);

	player2->SetMPIndex({ playerTileX,playerTileY }, { mouseTileX,mouseTileY });
	player2->sortOrder = playerTileY;
	
	// PLAYER EQUIP
	{
		player2->SetItemId(quickinven->GetItemId()); 
	}

	// TEST CODE : HOUR +1
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::F5))
		{
			hour += 1;
		}
	}

	// TEST CODE : day +1
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::F6))
		{
			ChangeDate();
		}
	}

	// TEST CODE : Crop lev up
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad1))
		{
			for (auto crop : parsnipPool.GetUseList())
			{
				crop->FullLevUp();
			}
			for (auto crop : potatoPool.GetUseList())
			{
				crop->FullLevUp();
			}
			for (auto crop : cauliflowerPool.GetUseList())
			{
				crop->FullLevUp();
			}
		}
	}

	// UI : TIME DATA SETTING
	{
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
			ChangeDate();
			/*hour = 0;
			day += 1;
			arrowSpin = 0;*/
		}
		if (hour == 2)
		{
			player2->ZeroEnergy();
			/*hour = 6;*/
			ChangeDate();
		}
		arrowSpin += dt * 0.2381f;
		timeArrow->SetOrigin(Origins::BC);
		timeArrow->sprite.setRotation(arrowSpin);
	}

	// UI : MONEY, TIME, DATE
	{
		texMoney->SetText(to_string(*player2->GetMoney()), 50, sf::Color::Black, Origins::TL, 101, 1675.f, 195.f);
	
		texHour->SetText(to_string(hour), 50, sf::Color::Black, Origins::TL, 101, 1710.f, 115.f);
		collon->SetText(":", 50, sf::Color::Black, Origins::TL, 101, 1755, 115.f);
		texMin->SetText(to_string(min), 50, sf::Color::Black, Origins::TL, 101, 1770.f, 115.f);

		StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);
		texDay->SetText(to_string(day), 50, sf::Color::Black, Origins::TL, 101, 1800.f, 12.f);
		dayday->SetText(stringTable->Get("DAY"), 50, sf::Color::Black, Origins::TR, 101, 1795.f, 12.f);
	
		energyBar->SetSize(sf::Vector2f(26.f, player2->GetEnergy() * 0.67));
		energyBar->SetPosition(energy->GetPosition().x- 26.f,energy->GetPosition().y - 10.f);
		energyBar->SetOrigin(Origins::BC);
	}

	// FARMING
	{
		if (player2->GetPlayerItemId() == ItemId::parsnipSeed
			|| player2->GetPlayerItemId() == ItemId::potatoSeed
			|| player2->GetPlayerItemId() == ItemId::coliSeed)
		{
			ItemId itemId = player2->GetPlayerItemId();
			selectTile->SetActive(true);
			selectTile->SetPosition({ mouseTileX * tileSize.x + mapLT.x, mouseTileY * tileSize.y + mapLT.y });

			if (abs(mouseTileX - playerTileX) < 2 && abs(mouseTileY - playerTileY) < 2
				&& dirtArray[mouseTileY][mouseTileX]->GetActive()
				&& !dirtArray[mouseTileY][mouseTileX]->GetIsPlanted())
			{
				selectTile->sprite.setTextureRect(RESOURCE_MGR.GetTextureRect("greenTile"));
				canPlant = true;
			}
			else
			{
				selectTile->sprite.setTextureRect(RESOURCE_MGR.GetTextureRect("redTile"));
				canPlant = false;
			}

			//PLANT CROP
			if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && canPlant)
			{
				if (player2->GetItemCount() > 0)
				{
					switch (itemId)
					{
					case ItemId::parsnipSeed:
						PlantParsnip(mouseTileX, mouseTileY);
						break;
					case ItemId::potatoSeed:
						PlantPotato(mouseTileX, mouseTileY);
						break;
					case ItemId::coliSeed:
						PlantCauli(mouseTileX, mouseTileY);
						break;
					default:
						break;
					}
				}
			}
		}
		else
		{
			selectTile->SetActive(false);
		}
	}

	//FADE
	{
		/*if (fadingIn)
		{
			fadeRectangle->SetActive(true);
			FadeIn(dt);
		}*/
	}
	
	// LOCATION ENTER
	{
		/*if (location == Location::Farm && Utils::Distance(houseOutEnter, player2->GetPosition()) <= 30.f &&
			INPUT_MGR.GetMouseButtonUp(sf::Mouse::Right))
		{	 
			for (auto go : gameObjects)
			{
				if (go->GetActive())
				{
					if (go->GetName() == "homeTap")
						continue;
					go->SetActive(false);
				}
				else
				{
					if (go->GetName() == "hoedirt" || go->GetName() == "shopInterior")
						continue;
					go->SetActive(true);
				}
			}
			SetAct(true);
			location = Location::Home;
			player2->ClearWalls();
			for (int i = 0; i < houseWalls.size(); ++i)
			{
				player2->SetWallBounds(houseWalls[i]);
			}
			player2->SetPosition(houseInEnter);
		}
		else if (location == Location::Farm && Utils::Distance(shopOutEnter, player2->GetPosition()) <= 30.f &&
			INPUT_MGR.GetMouseButtonUp(sf::Mouse::Right))
		{
			for (auto go : gameObjects)
			{
				if (go->GetActive())
				{
					if (go->GetName() == "homeTap")
						continue;
					go->SetActive(false);
				}
				else
				{
					if (go->GetName() == "homeInterior" || go->GetName() == "bedding" || go->GetName() == "hoedirt")
						continue;
					go->SetActive(true);
				}
			}
			SetAct(true);
			player2->ClearWalls();
			for (int i = 0; i < shopWalls.size(); ++i)
			{
				player2->SetWallBounds(shopWalls[i]);
			}
			location = Location::Shop;
			player2->SetPosition(shopInEnter);
		}*/
	}

	// LOCATION PATTERN
	{
		//cout << player2->GetPosition().x << "," << player2->GetPosition().y << endl;
		switch (location)
			{
			case Location::Home:
				if (fadingOut)
				{
					fadeRectangle->SetActive(true);
					FadeOut(dt);
				}
				// BEDDING COLLIDE
				{
					if (!player2->sprite.getGlobalBounds().intersects(bedding->sprite.getGlobalBounds()))
					{
						init = true;
					}

					if (init && player2->collider.getGlobalBounds().intersects(bedding->sprite.getGlobalBounds()))
					{
						if (!once && player2->collider.getPosition().x >= bedding->GetPosition().x + bedding->sprite.getGlobalBounds().width / 2.f)
						{
							homeTap->homeTapOn = true;
							homeTap->TapOnOff();
							once = true;
						}
					}
					else
					{
						once = false;
						homeTap->homeTapOn = false;
						homeTap->TapOnOff();
					}
				}
				// SAVE
				{
					if (homeTap->save)
					{
						sData = { *player2->GetPlayerItemList(), *player2->GetTotalEarningsInt(), *player2->GetMoney(), player2->GetEnergy(), min, hour, day, stones, timbers, weeds, trees, activeDirtIndex, parsnipPool.GetUseList(), potatoPool.GetUseList(), cauliflowerPool.GetUseList()};
						SAVELOAD_DATA.SaveCSV(&sData);
						//ChangeDate();
						homeTap->save = false;
						ChangeDate();
					}
				}
				// OUT
				{
					if (player2->GetCollider().intersects(homeExit.getGlobalBounds()) && changeLocation)
					{
						fadingOut = true;
					}
					if (!changeLocation && !fadingOut)
					{
						for (auto go : gameObjects)
						{
							if (go->GetActive())
							{
								if (go->GetName() == "homeTap")
									continue;
								go->SetActive(false);

							}
							else
							{
								if (go->GetName() == "shopInterior" || go->GetName() == "hoedirt")
									continue;
								go->SetActive(true);
							}
						}
						SetAct(true);
						player2->SetPosition(houseOutEnter);
						player2->ClearWalls();
						for (int i = 0; i < farmWalls.size(); ++i)
						{
							player2->SetWallBounds(farmWalls[i]);
						}
						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < col; j++)
							{
								auto foundIt = std::find_if(activeDirtIndex.begin(), activeDirtIndex.end(),
									[&](const std::pair<int, int>& pair) {
										return pair.first == i && pair.second == j;
									});
								if (foundIt != activeDirtIndex.end())
								{
									dirtArray[i][j]->SetActive(true);
								}
							}
						}
						location = Location::Farm; 
						changeLocation = true;
						fadingIn = true;
					}
				}
				if (fadingIn)
				{
					fadeRectangle->SetActive(true);
					FadeIn(dt);
				}
				break;
			case Location::Shop:
				// OUT
				{
					if (fadingOut)
					{
						fadeRectangle->SetActive(true);
						FadeOut(dt);
					}
					if (player2->GetCollider().intersects(shopExit.getGlobalBounds()) && changeLocation)
					{
						fadingOut = true;
					}
					if (!changeLocation && !fadingOut)
					{
						for (auto go : gameObjects)
						{
							if (go->GetActive())
							{
								if (go->GetName() == "homeTap")
									continue;
								go->SetActive(false);
							}
							else
							{
								if (go->GetName() == "homeInterior" || go->GetName() == "bedding" || go->GetName() == "hoedirt")
									continue;
								go->SetActive(true);
							}
						}
						SetAct(true);
						player2->ClearWalls();
						for (int i = 0; i < farmWalls.size(); ++i)
						{
							player2->SetWallBounds(farmWalls[i]);
						}
						player2->SetPosition(shopOutEnter);
						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < col; j++)
							{
								auto foundIt = std::find_if(activeDirtIndex.begin(), activeDirtIndex.end(),
									[&](const std::pair<int, int>& pair) {
										return pair.first == i && pair.second == j;
									});
								if (foundIt != activeDirtIndex.end())
								{
									dirtArray[i][j]->SetActive(true);
								}
							}
						}
						location = Location::Farm;
						changeLocation = true;
						fadingIn = true;
					}
					if (fadingIn)
					{
						fadeRectangle->SetActive(true);
						FadeIn(dt);
					}
					break;
				}
			case Location::Farm:
				if (fadingOut)
				{
					fadeRectangle->SetActive(true);
					FadeOut(dt);
				}
				if (location == Location::Farm && Utils::Distance(houseOutEnter, player2->GetPosition()) <= 30.f &&
					INPUT_MGR.GetMouseButtonUp(sf::Mouse::Right) && changeLocation)
				{
					fadingOut = true;
					nextlocation = Location::Home;
					/*for (auto go : gameObjects)
					{
						if (go->GetActive())
						{
							if (go->GetName() == "homeTap")
								continue;
							go->SetActive(false);
						}
						else
						{
							if (go->GetName() == "hoedirt" || go->GetName() == "shopInterior")
								continue;
							go->SetActive(true);
						}
					}
					SetAct(true);
					location = Location::Home;
					player2->ClearWalls();
					for (int i = 0; i < houseWalls.size(); ++i)
					{
						player2->SetWallBounds(houseWalls[i]);
					}
					player2->SetPosition(houseInEnter);*/
				}
				else if (location == Location::Farm && Utils::Distance(shopOutEnter, player2->GetPosition()) <= 30.f &&
					INPUT_MGR.GetMouseButtonUp(sf::Mouse::Right) && changeLocation)
					{
						fadingOut = true;
						nextlocation = Location::Shop;
						/*for (auto go : gameObjects)
						{
							if (go->GetActive())
							{
								if (go->GetName() == "homeTap")
									continue;
								go->SetActive(false);
							}
							else
							{
								if (go->GetName() == "homeInterior" || go->GetName() == "bedding" || go->GetName() == "hoedirt")
									continue;
								go->SetActive(true);
							}
						}
						SetAct(true);
						player2->ClearWalls();
						for (int i = 0; i < shopWalls.size(); ++i)
						{
							player2->SetWallBounds(shopWalls[i]);
						}
						location = Location::Shop;
						player2->SetPosition(shopInEnter);*/
				}
				if (!changeLocation && !fadingOut)
				{
					if (nextlocation == Location::Home)
					{
						for (auto go : gameObjects)
						{
							if (go->GetActive())
							{
								if (go->GetName() == "homeTap")
									continue;
								go->SetActive(false);
							}
							else
							{
								if (go->GetName() == "hoedirt" || go->GetName() == "shopInterior")
									continue;
								go->SetActive(true);
							}
						}
						SetAct(true);
						location = Location::Home;
						player2->ClearWalls();
						for (int i = 0; i < houseWalls.size(); ++i)
						{
							player2->SetWallBounds(houseWalls[i]);
						}
						player2->SetPosition(houseInEnter);
						changeLocation = true;
						fadingIn = true;
					}
					else if (nextlocation == Location::Shop)
					{
						for (auto go : gameObjects)
						{
							if (go->GetActive())
							{
								if (go->GetName() == "homeTap")
									continue;
								go->SetActive(false);
							}
							else
							{
								if (go->GetName() == "homeInterior" || go->GetName() == "bedding" || go->GetName() == "hoedirt")
									continue;
								go->SetActive(true);
							}
						}
						SetAct(true);
						player2->ClearWalls();
						for (int i = 0; i < shopWalls.size(); ++i)
						{
							player2->SetWallBounds(shopWalls[i]);
						}
						location = Location::Shop;
						player2->SetPosition(shopInEnter);
						changeLocation = true;
						fadingIn = true;
					}
				}
				if (fadingIn)
				{
					fadeRectangle->SetActive(true);
					FadeIn(dt);
				}
				break;
			}
	}

	// PLAYER MOVE PATTERN
	{
		if (homeTap->homeTapOn || shopTap->shopTapOn || inven->GetInvenOff())
		{
			player2->move = false;
			player2->MoneyUpdate();
		}
		else
		{
			player2->move = true;
		}
	}
	
	//SET VIEW
	{
		if(location == Location::Farm)
		{
			sf::Vector2f newCenter = player2->GetPosition();
			if (player2->GetPosition().x <= mapLT.x + FRAMEWORK.GetWindowSize().x / 2)
			{
				newCenter.x = mapLT.x + FRAMEWORK.GetWindowSize().x / 2;
			}
			if(player2->GetPosition().y <= mapLT.y + FRAMEWORK.GetWindowSize().y / 2)
			{
				newCenter.y = mapLT.y + FRAMEWORK.GetWindowSize().y / 2;
			}
			if (player2->GetPosition().x >= mapLT.x + mapSize.x - FRAMEWORK.GetWindowSize().x / 2)
			{
				newCenter.x = mapLT.x + mapSize.x - FRAMEWORK.GetWindowSize().x / 2;
			}
			if (player2->GetPosition().y >= mapLT.y + mapSize.y - FRAMEWORK.GetWindowSize().y / 2)
			{
				newCenter.y = mapLT.y + mapSize.y - FRAMEWORK.GetWindowSize().y / 2;
			}
			worldView.setCenter(newCenter);
		}
		else
		{
			worldView.setCenter(player2->GetPosition());
		}
	}

	// EDITOR ON
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			SCENE_MGR.ChangeScene(SceneId::Editor);
		}
	}

	// ITEM ROOTING TEST CODE
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num0))
		{
			SpawnRootingItem(ItemId::branch, {0,0});
		}
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num9))
		{
			SpawnRootingItem(ItemId::coal, { 0,0 });
		}
	}
	
	// QUICK & INVEN ONOFF
	{
		if (inven->GetInvenOff() || shopTap->shopTapOn || homeTap->homeTapOn)
		{
			quickinven->SetActive(false);
		}
		else
		{
			quickinven->SetActive(true);
		}

		if (shopTap->shopTapOn || homeTap->homeTapOn)
		{
			inven->invenTapOn = false;
		}
		else
		{
			inven->invenTapOn = true;
		}
	}

	// PLAYER OBJECT HIT TEST CODE
	{
		timer += dt;
		if (abs(mouseTileX - playerTileX) < 2 && abs(mouseTileY - playerTileY) < 2 && location == Location::Farm)
		{
			// HARVEST CROP
			{
				/*if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) || INPUT_MGR.GetMouseButtonDown(sf::Mouse::Right))
				{
					if (dirtArray[mouseTileY][mouseTileX]->GetIsPlanted())
					{
						CropId id = dirtArray[mouseTileY][mouseTileX]->GetCropId();
						switch (id)
						{
						case CropId::Parsnip:
							HarvestParsnip(mouseTileX, mouseTileY);
							break;
						case CropId::Potato:
							HarvestPotato(mouseTileX, mouseTileY);
							break;
						case CropId::Cauliflower:
							HarvestCauli(mouseTileX, mouseTileY);
							break;
						default:
							break;
						}
					}
				}*/
			}
			if (!(abs(mouseTileX - playerTileX) == 0 && abs(mouseTileY - playerTileY) == 0))
			{
				if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && player2->GetPlayerItemId() == ItemId::pick)
				{
					if (timer >= 0.5f)
					{
						timer = 0.f;
						HitStone(mouseTileX, mouseTileY);
						HitWeed(mouseTileX, mouseTileY);
						if (dirtArray[mouseTileY][mouseTileX]->GetActive())
						{
							switch (dirtArray[mouseTileY][mouseTileX]->GetIsPlanted())
							{
							case true:
								dirtArray[mouseTileY][mouseTileX]->GetCrop()->bang = true;
								dirtArray[mouseTileY][mouseTileX]->RemoveCrop();
								break;
							case false:
								dirtArray[mouseTileY][mouseTileX]->SetActive(false);
								activeDirtIndex.erase(
									std::remove_if(activeDirtIndex.begin(), activeDirtIndex.end(),
										[&](const std::pair<int, int>& pair) {
											return pair.first == mouseTileY || pair.second == mouseTileX;
										}), activeDirtIndex.end());

								dirtArray[mouseTileY][mouseTileX]->Reset();
								break;
							default:
								break;
							}
						}
					}
				}
				else if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && player2->GetPlayerItemId() == ItemId::ax)
				{
					if (timer >= 0.5f)
					{
						timer = 0.f;
						HitTree(mouseTileX, mouseTileY);
						HitTimber(mouseTileX, mouseTileY);
						HitWeed(mouseTileX, mouseTileY);
					}
				}
				else if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && player2->GetPlayerItemId() == ItemId::hook)
				{
					if (timer >= 0.5f)
					{
						timer = 0.f;
						HitWeed(mouseTileX, mouseTileY);
					}
				}
				else if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && player2->GetPlayerItemId() == ItemId::homi)
				{
					
					if (timer >= 0.5f)
					{
						timer = 0.f;
						if (!HasObjectAt(mouseTileX, mouseTileY) && !dirtArray[mouseTileY][mouseTileX]->GetActive()
							&& location == Location::Farm)
						{
							dirtArray[mouseTileY][mouseTileX]->SetActive(true);
							activeDirtIndex.push_back(std::make_pair(mouseTileY, mouseTileX));
							dirtArray[mouseTileY][mouseTileX]->SetCurrentDay(day);
						}
					}
				}
				else if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && player2->GetPlayerItemId() == ItemId::waterCan)
				{
					if (dirtArray[mouseTileY][mouseTileX]->GetActive())
					{
						dirtArray[mouseTileY][mouseTileX]->SetIsWatered(true);
					}
				}
			}
		}
	}

	//SET NIGHT TEST CODE
	{
		//night->SetOrigin(Origins::MC);
		//night->SetPosition(player2->GetPosition());
	}
}

void SceneGame::Draw(sf::RenderWindow& window) 
{
	Scene::Draw(window);
}

void SceneGame::SpawnRootingItem(ItemId id, sf::Vector2f pos)
{
	const ItemInfo* info = DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem)->Get(id);
	rootingItems.push_back((RootingItem*)AddGo(new RootingItem(info->itemId, info->resource, info->name_e, info->nickName))); // 아이템 먹으면 딜리트
	for (auto r : rootingItems)
	{
		r->Reset();
	}
	rootingItems.back()->SetPosition(pos); 
	rootingItems.back()->SetPlayer(player2); 
	rootingItems.back()->SetPosY(pos.y); 
	rootingItems.back()->sprite.setScale(4.f, 4.f);
	rootingItems.back()->SetOrigin(Origins::MC);
	rootingItems.back()->sortLayer = 2;
}

void SceneGame::SetAct(bool is)
{
	player2->SetActive(is);
	energy->SetActive(is);
	info->SetActive(is);
	timeArrow->SetActive(is);
	inven->SetActive(is);
	quickinven->SetActive(is);
	energyBar->SetActive(is);
	texMoney->SetActive(is);
	texMin->SetActive(is);
	texHour->SetActive(is);
	collon->SetActive(is);
	texDay->SetActive(is);
	dayday->SetActive(is);
}

void SceneGame::HitStone(int x, int y)
{
	for (auto it = stones.begin(); it != stones.end();)
	{
		int stoneX = static_cast<int>(((*it)->GetPosition().x - mapLT.x) / tileSize.x);
		int stoneY = static_cast<int>(((*it)->GetPosition().y - mapLT.y) / tileSize.y);

		if (stoneX == x && stoneY == y)
		{
			(*it)->Hit(1);
			if ((*it)->GetHp() <= 0)
			{
				sf::FloatRect wal = (*it)->GetCollider();
				auto wallIt = std::find(farmWalls.begin(), farmWalls.end(), wal);
				if (wallIt != farmWalls.end())
				{
					farmWalls.erase(wallIt);//해당 돌의 콜라이더 삭제
				}
				//(*it)->SetOrigin(Origins::BC);
				(*it)->SetBang();

				//(*it)->SetActive(false);//해당 돌을 화면에서 안보이게 제거
				RemoveGo(*it);
				it = stones.erase(it);//돌의 백터 배열에서 제거
				player2->ClearWalls();//플레이어가 가지고있는 콜라이더 배열 초기화

				SpawnRootingItem(ItemId::stone, { tileSize.x * stoneX + mapLT.x, tileSize.y * stoneY + mapLT.y });
				int pick = Utils::RadomOneOrTwo(1, 2);
				if (pick == 1)
				{
					SpawnRootingItem(ItemId::coal, { tileSize.x * stoneX + mapLT.x, tileSize.y * stoneY + mapLT.y });
				}

				EffectGo* effect = (EffectGo*)AddGo(new EffectGo("animations/Stone.csv", "Stone"));
				effect->sortLayer = 10;
				effect->SetPosition(tileSize.x * stoneX + mapLT.x, tileSize.y * stoneY + mapLT.y);
				effect->Init();
				effect->Reset();
				effect->SetScale(4.5f, 4.5f);
				effect->SetOrigin(Origins::TL);
				effects.push_back(effect);

				//walls 플레이어가 가지고있는 walls가 동일함 같은 인덱스? 일단 보류
				for (int i = 0; i < farmWalls.size(); ++i)
				{
					player2->SetWallBounds(farmWalls[i]);//다시 콜라이더 배열 업데이트
				}
			}
			break;
		}
		else
		{
			++it;
		}

	}
}

void SceneGame::HitTimber(int x, int y)
{
	for (auto it = timbers.begin(); it != timbers.end();)
	{
		int timberX = static_cast<int>(((*it)->GetPosition().x - mapLT.x) / 72);
		int timberY = static_cast<int>(((*it)->GetPosition().y - mapLT.y) / 72);
		//ItemId* itme = player2->GetPlayerItemId();

		if (timberX == x && timberY == y)
		{
			(*it)->Hit(1);
			//std::cout << (*it)->GetHp() << std::endl;
			if ((*it)->GetHp() <= 0)
			{
				sf::FloatRect wal = (*it)->GetCollider();
				auto wallIt = std::find(farmWalls.begin(), farmWalls.end(), wal);
				if (wallIt != farmWalls.end())
				{
					farmWalls.erase(wallIt);
				}

				(*it)->SetBang();
				//(*it)->SetActive(false);
				RemoveGo(*it);
				it = timbers.erase(it);
			
				player2->ClearWalls();

				SpawnRootingItem(ItemId::branch, { tileSize.x * timberX + mapLT.x, tileSize.y * timberY + mapLT.y });

				EffectGo* effect = (EffectGo*)AddGo(new EffectGo("animations/Timber.csv", "Timber"));
				effect->sortLayer = 10; 
				effect->SetPosition(tileSize.x * timberX + mapLT.x, tileSize.y * timberY + mapLT.y); 
				effect->Init();
				effect->Reset();
				effects.push_back(effect);

				
				for (int i = 0; i < farmWalls.size(); ++i)
				{
					player2->SetWallBounds(farmWalls[i]);
				}
			}
			break;
		}
		else
		{
			++it;
		}

	}
}

void SceneGame::HitTree(int x, int y)
{
	for (auto it = trees.begin(); it != trees.end();)
	{
		int treeX = static_cast<int>(((*it)->stump->GetPosition().x - mapLT.x) / 72);
		int treeY = static_cast<int>(((*it)->stump->GetPosition().y - mapLT.y) / 72);
		
		if (treeX == x && treeY == y)
		{
			(*it)->stump->Hit(1);
			(*it)->Hit();
			if ((*it)->stump->GetHp() == 5)
			{
				(*it)->TreeRotation();
				for (int i = 0; i < 7; ++i)
				{
					SpawnRootingItem(ItemId::branch, { (tileSize.x * treeX + mapLT.x)/* + 200.f*/, (tileSize.y * treeY + mapLT.y) });
				}
			}

			if ((*it)->stump->GetHp() == 0)  
			{
				sf::FloatRect wal = (*it)->stump->GetCollider();
				auto wallIt = std::find(farmWalls.begin(), farmWalls.end(), wal);
				if (wallIt != farmWalls.end())
				{
					farmWalls.erase(wallIt);
				}

				if ((*it)->GetBranchNick() == "branch")
				{
					std::cout << "branch" << std::endl;
					SpawnRootingItem(ItemId::mapleSeed, { tileSize.x * treeX + mapLT.x, tileSize.y * treeY + mapLT.y });
				}
				else if ((*it)->GetBranchNick() == "branch2")
				{
					std::cout << "branch2" << std::endl;
					SpawnRootingItem(ItemId::acorn, { tileSize.x * treeX + mapLT.x, tileSize.y * treeY + mapLT.y });
				}
				else if ((*it)->GetBranchNick() == "branch3")
				{
					std::cout << "branch3" << std::endl;
					SpawnRootingItem(ItemId::pineCone, { tileSize.x * treeX + mapLT.x, tileSize.y * treeY + mapLT.y });
				}

				(*it)->SetActive(false);
				player2->ClearWalls();
				RemoveGo(*it);
				it = trees.erase(it); 
				for (int i = 0; i < 7; ++i)
				{
					SpawnRootingItem(ItemId::branch, { tileSize.x * treeX + mapLT.x, tileSize.y * treeY + mapLT.y });
				}

				for (int i = 0; i < farmWalls.size(); ++i)
				{
					player2->SetWallBounds(farmWalls[i]);
				}
			}
			break;
		}
		else
		{
			++it;
		}

	}
}

void SceneGame::HitWeed(int x, int y)
{
	for (auto it = weeds.begin(); it != weeds.end();)
	{
		int weedX = static_cast<int>(((*it)->GetPosition().x - mapLT.x) / 72);
		int weedY = static_cast<int>(((*it)->GetPosition().y - mapLT.y) / 72);
		
		if (weedX == x && weedY == y)
		{
			(*it)->Hit(1);
			
			if ((*it)->GetHp() == 0)
			{
				sf::FloatRect wal = (*it)->GetCollider();
				auto wallIt = std::find(farmWalls.begin(), farmWalls.end(), wal);
				if (wallIt != farmWalls.end())
				{
					farmWalls.erase(wallIt);
				}
				(*it)->SetBang(); 
				RemoveGo(*it); 
				it = weeds.erase(it);

				player2->ClearWalls();

				SpawnRootingItem(ItemId::fiver, { tileSize.x * weedX + mapLT.x, tileSize.y * weedY + mapLT.y });

				EffectGo* effect = (EffectGo*)AddGo(new EffectGo("animations/Weed.csv", "Weed")); 
				effect->sortLayer = 10; 
				effect->SetPosition(tileSize.x * weedX + mapLT.x, tileSize.y * weedY + mapLT.y); 
				effect->Init(); 
				effect->Reset(); 
				effects.push_back(effect); 

				for (int i = 0; i < farmWalls.size(); ++i)
				{
					player2->SetWallBounds(farmWalls[i]);
				}
			}
			break;
		}
		else
		{
			++it;
		}
	}
}

bool SceneGame::HasObjectAt(int x, int y)
{
	for (auto stone : stones)
	{
		if (stone->GetIndex().x == x && stone->GetIndex().y == y)
		{
			return true;
		}
	}
	for (auto timber : timbers)
	{
		if (timber->GetIndex().x == x && timber->GetIndex().y == y)
		{
			return true;
		}
	}
	for (auto weed : weeds)
	{
		if (weed->GetIndex().x == x && weed->GetIndex().y == y)
		{
			return true;
		}
	}
	for (auto tree : trees)
	{
		if (tree->stump->GetIndex().x == x && tree->stump->GetIndex().y == y)
		{
			return true;
		}
	}
	return false;
}

void SceneGame::SetGreenTile()
{
}

void SceneGame::PlantParsnip(int x, int y)
{
	Parsnip* parsnip = parsnipPool.Get();
	parsnip->SetPosition({ x * tileSize.x + mapLT.x, y * tileSize.y + mapLT.y });
	parsnip->SetDirtTile(dirtArray[y][x]);
	parsnip->SetDate(day);
	parsnip->SetIndex(x, y);
	parsnip->SetIsWatered(dirtArray[y][x]->GetIsWatered());
	parsnip->sortOrder = y;
	AddGo(parsnip);

	dirtArray[y][x]->PlantCrop(parsnip);

	player2->RemovePlayerItem(ItemId::parsnipSeed);
}

void SceneGame::PlantPotato(int x, int y)
{
	Potato* potato = potatoPool.Get();
	potato->SetPosition({ x * tileSize.x + mapLT.x, y * tileSize.y + mapLT.y });
	potato->SetDirtTile(dirtArray[y][x]);
	potato->SetDate(day);
	potato->SetIndex(x, y);
	potato->SetIsWatered(dirtArray[y][x]->GetIsWatered());
	AddGo(potato);

	dirtArray[y][x]->PlantCrop(potato);

	player2->RemovePlayerItem(ItemId::potatoSeed);
}

void SceneGame::PlantCauli(int x, int y)
{
	Cauliflower* cauli = cauliflowerPool.Get();
	cauli->SetPosition({ x * tileSize.x + mapLT.x, y * tileSize.y + mapLT.y });
	cauli->SetDirtTile(dirtArray[y][x]);
	cauli->SetDate(day);
	cauli->SetIndex(x, y);
	cauli->SetIsWatered(dirtArray[y][x]->GetIsWatered());
	AddGo(cauli);

	dirtArray[y][x]->PlantCrop(cauli);

	player2->RemovePlayerItem(ItemId::coliSeed);
}

void SceneGame::HarvestParsnip(int x, int y)
{
	
	auto crop = (Parsnip*)dirtArray[y][x]->GetCrop();
	if (crop->GetCanHarvest())
	{
		dirtArray[y][x]->RemoveCrop();

		RemoveGo(crop);
		parsnipPool.Return(crop);
		player2->Harvest();
		player2->AddPlayerItem(ItemId::parsnip);
		
	}
}

void SceneGame::HarvestPotato(int x, int y)
{
	auto crop = (Potato*)dirtArray[y][x]->GetCrop();
	if (crop->GetCanHarvest())
	{
		dirtArray[y][x]->RemoveCrop();

		RemoveGo(crop);
		potatoPool.Return(crop);
		player2->Harvest();
		player2->AddPlayerItem(ItemId::potato);
	}
}

void SceneGame::HarvestCauli(int x, int y)
{
	auto crop = (Cauliflower*)dirtArray[y][x]->GetCrop();
	if (crop->GetCanHarvest())
	{
		dirtArray[y][x]->RemoveCrop();

		RemoveGo(crop);
		cauliflowerPool.Return(crop);
		player2->Harvest();
		player2->AddPlayerItem(ItemId::coli);
	}
}

void SceneGame::ChangeDate()
{
	day += 1;

	time = 0;
	hour = 6;
	min = 0;
	arrowSpin = 0;
}

void SceneGame::ObjectLoad(unordered_map<int, ObjectInfo> table)
{
	for (auto obj : table)
	{
		auto objInfo = obj.second;
		sf::IntRect objRect(objInfo.left, objInfo.top, objInfo.width, objInfo.height);
		if (obj.second.type == ObjType::Stone)
		{
			Stone* stone = (Stone*)AddGo(new Stone("map/object.png", "stone" + to_string(stoneCount)));
			stone->SetType(objInfo.indexX, objInfo.indexY, objRect, testFarmMap->GetTileSize());
			stone->SetHp(1);
			stones.push_back(stone);
			stone->sortLayer = 1;
			stone->sortOrder = obj.second.indexY;
			stoneCount++;
		}
		else if (obj.second.type == ObjType::Timber)
		{
			Timber* timber = (Timber*)AddGo(new Timber("map/object.png", "timber" + to_string(timberCount)));
			timber->SetType(objInfo.indexX, objInfo.indexY, objRect, testFarmMap->GetTileSize());
			timber->SetHp(1);
			timbers.push_back(timber);
			timber->sortLayer = 1;
			timber->sortOrder = obj.second.indexY;
			timberCount++;
		}
		else if (obj.second.type == ObjType::Weed)
		{
			Weed* weed = (Weed*)AddGo(new Weed("map/object.png", "weed" + to_string(weedCount)));
			weed->SetHp(1);
			weed->SetType(objInfo.indexX, objInfo.indexY, objRect, testFarmMap->GetTileSize());
			weeds.push_back(weed);
			weed->sortLayer = 1;
			weed->sortOrder = obj.second.indexY;
			weedCount++;
		}
		else if (obj.second.type == ObjType::Tree)
		{
			switch ((int)objInfo.left)
			{
			case 144: //2
			{
				branchNick = "branch2";
				branchId = "map/tree2_spring.png";
				break;
			}
			case 160: //1
			{
				branchNick = "branch";
				branchId = "map/tree1_spring.png";
				break;
			}
			case 176: //3
			{
				branchNick = "branch3";
				branchId = "map/tree3_spring.png";
				break;
			}
			default:
				break;
			}
			Tree* tree = (Tree*)AddGo(new Tree("tree" + to_string(treeCount), branchId, "map/object.png", branchNick, "stump"));
			tree->stump->SetType(objInfo.indexX, objInfo.indexY, objRect, testFarmMap->GetTileSize());
			tree->stump->SetHp(15);
			trees.push_back(tree);
			tree->sortLayer = 1;
			tree->sortOrder = obj.second.indexY;
			treeCount++;
		}
	}
}

void SceneGame::FileLoad(bool load)
{
	if (load)
	{
		SAVELOAD_DATA.LoadCSV(&sData);
		player2->LoadData(sData.pl_ItemList, sData.pl_totalMoney, sData.pl_money, sData.pl_energy);
		min = sData.game_min;
		hour = sData.game_hour;
		day = sData.game_day;
		ObjectLoad(SAVELOAD_DATA.table);
		activeDirtIndex = sData.activeDirtIndex;
		CropLoad(parsnipPool, SAVELOAD_DATA.parsnip);
		CropLoad(potatoPool, SAVELOAD_DATA.potato);
		CropLoad(cauliflowerPool, SAVELOAD_DATA.cauliflower);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				dirtArray[i][j]->load = true;
			}
		}
	}
	else
	{
		min = 0;
		hour = 6;
		day = 1;
		Objtable = (ObjectTable*)(new ObjectTable());
		Objtable->Load();
		ObjectLoad(Objtable->GetTable());
		player2->load = false;
		for (auto i : parsnipPool.GetPool())
		{
			i->load = false;
		}
		for (auto i : potatoPool.GetPool())
		{
			i->load = false;
		}
		for (auto i : cauliflowerPool.GetPool())
		{
			i->load = false;
		}
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				dirtArray[i][j]->load = false;
			}
		}
		activeDirtIndex.clear();
	}
}

void SceneGame::FadeIn(float dt)
{
	cout << "fadein" << endl;
	fadeAlpha -= fadeSpeed * dt;
	fadeRectangle->rectangle.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));
	if (fadeAlpha <= 0.0f)
	{
		fadeAlpha = 0.0f;
		fadingIn = false;
	}
}

void SceneGame::FadeOut(float dt)
{
	cout << "fadeOut" << endl;
	fadeAlpha += fadeSpeed * dt;
	fadeRectangle->rectangle.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));
	if (fadeAlpha >= 255.0f)
	{
		changeLocation = false;
		fadeAlpha = 255.0f;
		fadingOut = false;
		//fadingIn = true;
	}
}
