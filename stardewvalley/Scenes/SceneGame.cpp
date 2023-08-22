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
#include "ObjectTable.h"
#include "Stone.h"
#include "Timber.h"
#include "Weed.h"
#include "Tree.h"
#include "SaveLoadData.h"

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

	// TEST MAP
	{	//0818 맵툴 맵 적용]
		//땅
		testFarmMap = (TileMap*)AddGo(new TileMap("map/spring_outdoorsTileSheet_cut.png", "MapTile1"));
		testFarmMap->Reset();
		testFarmMap->Load("tables/newMapLayer1.csv");
		testFarmMap->SetOrigin(Origins::MC);
		//울타리나 절벽
		testFarmMap2 = (TileMap*)AddGo(new TileMap("map/spring_outdoorsTileSheet_cut.png", "MapTile2"));
		testFarmMap2->Reset();
		testFarmMap2->Load("tables/newMapLayer2.csv"); //투명한 타일 176, 0
		testFarmMap2->SetOrigin(Origins::MC);

		//testFarmMapObj = (TileMap*)AddGo(new TileMap("map/object.png", "MapObj"));
		//testFarmMapObj->Reset();
		//testFarmMapObj->Load("tables/newMapLayerObj.csv"); //투명한 타일 96, 16
		//testFarmMapObj->SetOrigin(Origins::MC);

		houseExterior = (SpriteGo*)AddGo(new SpriteGo("map/houses.png", "house", "house"));
		houseExterior->sprite.setScale(4.f, 4.f);
		houseExterior->SetOrigin(Origins::BC);
		houseExterior->collider.setScale(1.f, 0.3f);
		houseExterior->sortLayer = 1;

		shopExterior = (SpriteGo*)AddGo(new SpriteGo("map/spring_town.ko-KR.png", "shop", "shop"));
		shopExterior->sprite.setScale(4.f, 4.f);
		shopExterior->SetOrigin(Origins::BC);
		shopExterior->collider.setScale(1.f, 0.3f);
	}
	// OBJECT
	{
		Objtable = (ObjectTable*)(new ObjectTable());
		Objtable->Load();
		for (auto obj : Objtable->GetTable())
		{
			auto objInfo = obj.second;
			sf::IntRect objRect(objInfo.left, objInfo.top, objInfo.width, objInfo.height);
			if (obj.second.type == ObjType::Stone)
			{
				Stone* stone = (Stone*)AddGo(new Stone("map/object.png", "stone"+to_string(stoneCount)));
				stone->SetType(objInfo.indexX, objInfo.indexY, objRect, testFarmMap->GetTileSize());
				stone->SetHp(1);
				stones.push_back(stone);
				stone->sortLayer = 1;
				stoneCount++;
			}
			else if (obj.second.type == ObjType::Timber)
			{
				Timber* timber = (Timber*)AddGo(new Timber("map/object.png", "timber" + to_string(timberCount)));
				timber->SetType(objInfo.indexX, objInfo.indexY, objRect, testFarmMap->GetTileSize());
				timber->SetHp(1);
				timbers.push_back(timber);
				timber->sortLayer = 1;
				timberCount++;
			}
			else if (obj.second.type == ObjType::Weed)
			{
				Weed* weed = (Weed*)AddGo(new Weed("map/object.png", "weed" + to_string(weedCount)));
				weed->SetHp(1);
				weed->SetType(objInfo.indexX, objInfo.indexY, objRect, testFarmMap->GetTileSize());
				weeds.push_back(weed);
				weed->sortLayer = 1;
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
				tree->sortLayer = 2;
				treeCount++;
			}
		}
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
		//homeTap->SetActive(false);
	}

	//TEXT
	texMoney = (TextGo*)AddGo(new TextGo("TexMoney", "fonts/SDMiSaeng.ttf"));
	texMin = (TextGo*)AddGo(new TextGo("TexMin", "fonts/SDMiSaeng.ttf"));
	texHour = (TextGo*)AddGo(new TextGo("TexHour", "fonts/SDMiSaeng.ttf"));
	collon = (TextGo*)AddGo(new TextGo("Collon", "fonts/SDMiSaeng.ttf"));
	texDay = (TextGo*)AddGo(new TextGo("TexDay", "fonts/SDMiSaeng.ttf"));
	dayday = (TextGo*)AddGo(new TextGo("DayDay", "fonts/SDMiSaeng.ttf"));

	//test
	sf::Vector2f rectsize = { 72.f,72.f };
	testbox = (RectangleGo*)AddGo(new RectangleGo(rectsize)); 
	testbox->sortLayer = 3;
	testbox->SetColor(sf::Color(0,0,255,100));
	
 
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
	auto size = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = size * 0.5f;

	worldView.setSize(size);
	worldView.setCenter(0, 0);

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);

	
	shopTap->SetPierre(shopInterior->GetPierre());

	
	//testFarmMapObj->SetPosition(testFarmMap->GetPosition());

	tileSize = testFarmMap->GetTileSize();

	
	mapLT = { testFarmMap->vertexArray.getBounds().left, testFarmMap->vertexArray.getBounds().top };
	for (int i = 0; i < stones.size(); i++)
	{
		Stone* stone = (Stone*)FindGo("stone" + to_string(i));
		stone->SetMapLT(mapLT);
	}
	for (int i = 0; i < timbers.size(); i++)
	{
		Timber* timber = (Timber*)FindGo("timber" + to_string(i));
		timber->SetMapLT(mapLT);
	}
	for (int i = 0; i < weeds.size(); i++)
	{
		Weed* weed = (Weed*)FindGo("weed" + to_string(i));
		weed->SetMapLT(mapLT);
	}
	for (int i = 0; i < trees.size(); i++)
	{
		Tree* tree = (Tree*)FindGo("tree" + to_string(i));
		tree->stump->SetMapLT(mapLT);
	}

	houseExterior->SetPosition(mapLT.x + tileSize.x * housePos.x, mapLT.y + tileSize.y * housePos.y);
	walls.push_back(houseExterior->GetCollider());

	shopExterior->SetPosition(mapLT.x + tileSize.x * shopPos.x, mapLT.y + tileSize.y * shopPos.y);
	walls.push_back(shopExterior->GetCollider());

	for (int i = 0; i < stoneCount; i++)
	{
		Stone* stone = (Stone*)FindGo("stone" + to_string(i));
		walls.push_back(stone->GetCollider());
	}
	//맵 툴 충돌체 설정
	rapidcsv::Document doc("tables/newMapCollider.csv");

	for (int i = 2; i < doc.GetRowCount(); i++)
	{
		auto rows = doc.GetRow<int>(i);
		sf::FloatRect rect = { mapLT.x + rows[0] * tileSize.x, mapLT.y + rows[1] * tileSize.y, tileSize.x, tileSize.y };
		walls.push_back(rect);
	}

	for (int i = 0; i < stoneCount; i++)
	{
		Stone* stone = (Stone*)FindGo("stone" + to_string(i));
		walls.push_back(stone->GetCollider());
	}
	for (int i = 0; i < timberCount; ++i)
	{
		Timber* timber = (Timber*)FindGo("timber" + to_string(i));
		walls.push_back(timber->GetCollider());
	}
	for (int i = 0; i < weedCount; ++i)
	{
		Weed* weed = (Weed*)FindGo("weed" + to_string(i));
		walls.push_back(weed->GetCollider());
	}
	for (int i = 0; i < treeCount; ++i)
	{
		Tree* tree = (Tree*)FindGo("tree" + to_string(i));
		walls.push_back(tree->stump->GetCollider());
	}
	Scene::Enter();
	for (int i = 0; i < walls.size(); ++i)
	{
		player2->SetWallBounds(walls[i]);
	}
	
	

	//SAVELOAD_DATA.Load(player2, &day, &hour, &min, &time);
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	//나무 뒤로 가면 나무 투명화
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

	//UI(돈, 시간, 날짜)
	texMoney->SetText(to_string(*player2->GetMoney()), 50, sf::Color::Black, Origins::TL, 101, 1675.f, 195.f);
	
	texHour->SetText(to_string(hour), 50, sf::Color::Black, Origins::TL, 101, 1710.f, 115.f);
	collon->SetText(":", 50, sf::Color::Black, Origins::TL, 101, 1755, 115.f);
	texMin->SetText(to_string(min), 50, sf::Color::Black, Origins::TL, 101, 1770.f, 115.f);

	texDay->SetText(to_string(day), 50, sf::Color::Black, Origins::TL, 101, 1800.f, 12.f);
	dayday->SetText("Day: ", 50, sf::Color::Black, Origins::TR, 101, 1795.f, 12.f);
	
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
			SetAct(true);
			player2->SetPosition(-463.f, -770.f); 
			homeInterior->SetActive(false);
			bedding->SetActive(false);
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
			SetAct(true);	
			player2->SetPosition(419.f, 1866.f); //shop position
			homeInterior->SetActive(false);
			bedding->SetActive(false);
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::H))
	{
		if (!enterHome)
		{
			enterHome = true;
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
			SetAct(true);
			player2->SetPosition(193.f, 728.f); // �� �빮 ��ġ��
			shopInterior->SetActive(false);
			bedding->SetActive(true);
			homeTap->SetActive(true);
		}
		else
		{
			enterHome = false;
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
			SetAct(true);
			player2->SetPosition(193.f, 728.f);
			shopInterior->SetActive(false);
			bedding->SetActive(false);
			homeTap->SetActive(true);
		}
	}

	// PLAYER - BEDDING COLLIDE
	if (enterHome)
	{
		// ���߿� ��ǥ�� �ٲٱ�
		if (player2->sprite.getGlobalBounds().intersects(bedding->sprite.getGlobalBounds()))
		{
			std::cout << "�浹" << std::endl;
			if (!once)
			{
				homeTap->homeTapOn = true;
				homeTap->TapOnOff();
				once = true;
			}
		}
		else
		{
			once = false;
			//homeTap->SetActive(false);
			homeTap->homeTapOn = false;
			homeTap->TapOnOff();
		}
	}
	
	worldView.setCenter(player2->GetPosition());

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneId::Editor);
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num0))
	{
		SpawnRootingItem(ItemId::branch, {0,0});
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num9))
	{
		SpawnRootingItem(ItemId::coal, { 0,0 });
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

	if (inven->GetChageScene())
	{
		inven->SetChageScene(false);
		SCENE_MGR.ChangeScene(SceneId::Title);
	}

	//sf::Vector2f playerTilePos;

	//playerTilePos.x = (player2->GetPosition().x - mapLT.x) / 72.f;
	//playerTilePos.y = (player2->GetPosition().y - mapLT.y) / 72.f;

	//플레이어가 바라보고있는 타일

	int tileX = static_cast<int>((player2->GetPosition().x - mapLT.x) / 72);
	int tileY = static_cast<int>((player2->GetPosition().y - mapLT.y) / 72);
	sf::Vector2f direction = player2->GetDirection(); 

	if (direction.x > 0.f)
	{
		tileX = static_cast<int>((player2->GetPosition().x - mapLT.x) / 72);
		tileX += 1;
		//tileSize.x* tileX + mapLT.x;
		testbox->SetPosition(tileSize.x* tileX + mapLT.x, tileSize.y* tileY + mapLT.y);
	}
	else if (direction.x < 0.f)
	{
		tileX = static_cast<int>((player2->GetPosition().x - mapLT.x) / 72);
		tileX -= 1;
		//tileSize.x* tileX + mapLT.x;
		testbox->SetPosition(tileSize.x* tileX + mapLT.x, tileSize.y* tileY + mapLT.y);
	}
	else if (direction.y > 0.f)
	{
		tileY = static_cast<int>((player2->GetPosition().y - mapLT.y) / 72);
		tileY += 1;
		//tileSize.y* tileY + mapLT.y;
		testbox->SetPosition(tileSize.x* tileX + mapLT.x, tileSize.y* tileY + mapLT.y);
	}
	else if (direction.y < 0.f)
	{
		tileY = static_cast<int>((player2->GetPosition().y - mapLT.y) / 72);
		tileY -= 1;
		//tileSize.y* tileY + mapLT.y;
		testbox->SetPosition(tileSize.x* tileX + mapLT.x, tileSize.y* tileY + mapLT.y);
	}

	int BtileX = static_cast<int>((testbox->GetPosition().x - mapLT.x) / 72);
	int BtileY = static_cast<int>((testbox->GetPosition().y - mapLT.y) / 72);

	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left)&& player2->GetPlayerItemId() == ItemId::pick)
	{
		HitStone(BtileX, BtileY); 
	}
	
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && player2->GetPlayerItemId() == ItemId::ax)
	{
		HitTimber(BtileX, BtileY);
	}
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && player2->GetPlayerItemId() == ItemId::ax) 
	{
		HitTree(BtileX, BtileY); 
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
		r->SetPosition(pos);
	}
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
}

void SceneGame::HitStone(int x, int y)
{
	for (auto it = stones.begin(); it != stones.end();)
	{
		int stoneX = static_cast<int>(((*it)->GetPosition().x - mapLT.x) / 72);
		int stoneY = static_cast<int>(((*it)->GetPosition().y - mapLT.y) / 72);
		//ItemId* itme = player2->GetPlayerItemId();

		if (stoneX == x && stoneY == y)
		{
			(*it)->Hit(1);
			std::cout << (*it)->GetHp() << std::endl;
			if ((*it)->GetHp() <= 0)
			{
				sf::FloatRect wal = (*it)->GetCollider();
				auto wallIt = std::find(walls.begin(), walls.end(), wal);
				if (wallIt != walls.end())
				{
					walls.erase(wallIt);//해당 돌의 콜라이더 삭제
				}

				(*it)->SetActive(false);//해당 돌을 화면에서 안보이게 제거
				it = stones.erase(it);//돌의 백터 배열에서 제거
				//RemoveGo(*it);
				player2->ClearWalls();//플레이어가 가지고있는 콜라이더 배열 초기화

				//testbox->SetPosition(tileSize.x * tileX + mapLT.x, tileSize.y * tileY + mapLT.y);

				SpawnRootingItem(ItemId::stone, { tileSize.x * stoneX + mapLT.x, tileSize.y * stoneY + mapLT.y });

				//walls 플레이어가 가지고있는 walls가 동일함 같은 인덱스? 일단 보류
				for (int i = 0; i < walls.size(); ++i)
				{
					player2->SetWallBounds(walls[i]);//다시 콜라이더 배열 업데이트
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
			std::cout << (*it)->GetHp() << std::endl;
			if ((*it)->GetHp() <= 0)
			{
				sf::FloatRect wal = (*it)->GetCollider();
				auto wallIt = std::find(walls.begin(), walls.end(), wal);
				if (wallIt != walls.end())
				{
					walls.erase(wallIt);//해당 돌의 콜라이더 삭제
				}

				(*it)->SetActive(false);//해당 돌을 화면에서 안보이게 제거
				it = timbers.erase(it);//돌의 백터 배열에서 제거
				//RemoveGo(*it);
				player2->ClearWalls();//플레이어가 가지고있는 콜라이더 배열 초기화

				SpawnRootingItem(ItemId::branch, { tileSize.x * timberX + mapLT.x, tileSize.y * timberY + mapLT.y });

				//walls 플레이어가 가지고있는 walls가 동일함 같은 인덱스? 일단 보류
				for (int i = 0; i < walls.size(); ++i)
				{
					player2->SetWallBounds(walls[i]);//다시 콜라이더 배열 업데이트
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
		int treeX = static_cast<int>(((*it)->GetPosition().x - mapLT.x) / 72);
		int treeY = static_cast<int>(((*it)->GetPosition().y - mapLT.y) / 72);
		
		if (treeX == x && treeY == y)
		{
			(*it)->stump->Hit(1);
			if ((*it)->stump->GetHp() == 5)
			{
				(*it)->TreeRotation();
			}
			else if ((*it)->stump->GetHp() == 0)  
			{
				sf::FloatRect wal = (*it)->stump->GetCollider();
				auto wallIt = std::find(walls.begin(), walls.end(), wal);
				if (wallIt != walls.end())
				{
					walls.erase(wallIt);
				}

				(*it)->SetActive(false);
				it = trees.erase(it); 
				
				player2->ClearWalls();

				SpawnRootingItem(ItemId::branch, { tileSize.x * treeX + mapLT.x, tileSize.y * treeY + mapLT.y });

				for (int i = 0; i < walls.size(); ++i)
				{
					player2->SetWallBounds(walls[i]);
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