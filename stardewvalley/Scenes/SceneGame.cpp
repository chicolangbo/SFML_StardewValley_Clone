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

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	//csv파일을 통해서 로딩하는 것으로 변경
	
	// 김민지, 230807, 폴더 수정
	//resourceListPath = "tables/SceneGameResourceList.csv";
	resourceListPath = "scripts/defaultResourceList.csv";
	//

	/*resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/RubySheet.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/sprite_sheet.png"));
	resources.push_back(make_tuple(ResourceTypes::Texture, "graphics/background_sheet.png"));
	resources.push_back(make_tuple(ResourceTypes::Texture, "graphics/TitleButtons1.png"));
	resources.push_back(make_tuple(ResourceTypes::Texture, "graphics/TitleButtons2.png"));*/
}



void SceneGame::Init()
{
	Release();

	auto size = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = size * 0.5f;
	
	worldView.setSize(size);
	// 김민지, 230807, 테스트용 센터 변경
	worldView.setCenter(0,0);
	//

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);

	// 김민지, 230808, 임시맵 코드 추가
	testFarmMap = (SpriteGo*)AddGo(new SpriteGo("map/testFarmMap.png", "testFarmMap", "testFarmMap"));
	testFarmMap->sprite.setScale(3.f, 3.f);
	testFarmMap->SetOrigin(Origins::MC);
	testFarmMap->SetPosition(0, 0);
	house = (SpriteGo*)AddGo(new SpriteGo("map/houses.png", "house", "house"));
	house->sprite.setScale(4.f, 4.f);
	house->SetOrigin(Origins::BC);
	house->SetPosition(473, -785);
	house->collider.setScale(1.f, 0.3f);
	house->sortLayer = 11;

	shop = (SpriteGo*)AddGo(new SpriteGo("map/spring_town.ko-KR.png", "shop", "shop"));
	shop->sprite.setScale(4.f, 4.f);
	shop->SetOrigin(Origins::BC);
	shop->SetPosition(-537, -785);
	shop->collider.setScale(1.f, 0.3f); 

	shopInside = (SpriteGo*)AddGo(new SpriteGo("map/shopInside.png", "shopInside", "shopInside"));
	shopInside->sprite.setScale(4.f, 4.f);
	shopInside->SetOrigin(Origins::TL);
	shopInside->SetPosition(0, 0);
	shopInside->SetActive(false);
	pierre = (SpriteGo*)AddGo(new SpriteGo("graphics/Pierre.png", "pierre", "pierre"));
	pierre->sprite.setScale(5.f, 5.f);
	pierre->SetOrigin(Origins::MC);
	pierre->SetPosition(244.f, 1086.f);
	pierre->SetActive(false);
	robin = (SpriteGo*)AddGo(new SpriteGo("graphics/Robin.png", "robin", "robin"));
	robin->sprite.setScale(5.f, 5.f);
	robin->SetOrigin(Origins::MC);
	robin->SetPosition(352.f, 1086.f);
	robin->SetActive(false);

	shopCounter1 = (SpriteGo*)AddGo(new SpriteGo("map/shopInside.png", "shopCounter1", "shopCounter1"));
	shopCounter1->sprite.setScale(4.f, 4.f);
	shopCounter1->SetOrigin(Origins::TL);
	shopCounter1->SetPosition(48.f*4, 275.f*4);
	shopCounter1->SetActive(false);
	shopCounter2 = (SpriteGo*)AddGo(new SpriteGo("map/shopInside.png", "shopCounter2", "shopCounter2"));
	shopCounter2->sprite.setScale(4.f, 4.f);
	shopCounter2->SetOrigin(Origins::TL);
	shopCounter2->SetPosition(128.f*4, 254.f*4);
	shopCounter2->SetActive(false);

	shopMid1 = (SpriteGo*)AddGo(new SpriteGo("map/townInterior.png", "shopMid1", "shopMid1"));
	shopMid1->sprite.setScale(4.f, 4.f);
	shopMid1->SetOrigin(Origins::TL);
	shopMid1->SetPosition(48.f*4, 332.f*4);
	shopMid1->SetActive(false);

	shopMid2_1 = (SpriteGo*)AddGo(new SpriteGo("map/townInterior.png", "shopMid2_1", "shopMid2"));
	shopMid2_1->sprite.setScale(4.f, 4.f);
	shopMid2_1->SetOrigin(Origins::TL);
	shopMid2_1->SetPosition(160.f*4, 277.f*4);
	shopMid2_1->SetActive(false);

	shopMid2_2 = (SpriteGo*)AddGo(new SpriteGo("map/townInterior.png", "shopMid2_2", "shopMid2"));
	shopMid2_2->sprite.setScale(4.f, 4.f);
	shopMid2_2->SetOrigin(Origins::TL);
	shopMid2_2->SetPosition(160.f*4, 325.f*4);
	shopMid2_2->SetActive(false);

	shopMid3_1 = (SpriteGo*)AddGo(new SpriteGo("map/townInterior.png", "shopMid3_1", "shopMid3"));
	shopMid3_1->sprite.setScale(4.f, 4.8f);
	shopMid3_1->SetOrigin(Origins::TL);
	shopMid3_1->SetPosition(160.f*4, 375.f*4);
	shopMid3_1->SetActive(false);

	shopMid3_2 = (SpriteGo*)AddGo(new SpriteGo("map/townInterior.png", "shopMid3_2", "shopMid3"));
	shopMid3_2->sprite.setScale(4.f, 4.8f);
	shopMid3_2->SetOrigin(Origins::TL);
	shopMid3_2->SetPosition(224.f*4, 375.f*4);
	shopMid3_2->SetActive(false);

	shopBox = (SpriteGo*)AddGo(new SpriteGo("map/shopInside.png", "shopBox", "shopBox"));
	shopBox->sprite.setScale(4.f, 4.f);
	shopBox->SetOrigin(Origins::TL);
	shopBox->SetPosition(288.f*4, 434.f*4);
	shopBox->SetActive(false);

	shopWalls = (Wall*)AddGo(new Wall("shopWall"));
	shopWalls->SetType(Wall::Location::Shop);
	shopWalls->SetPos();
	shopWalls->SetActive(false);

	player2 = (Player2*)AddGo(new Player2());
	player2->SetOrigin(Origins::BC);
	player2->sortLayer=10;
	player2->collider.setScale(0.5f, 0.1f);

	//에너지 바 UI 일단 구현만/임형준
	energy = (SpriteGo*)AddGo(new SpriteGo("graphics/Cursors.ko-KR.png", "Energy", "Energy"));
	energy->SetOrigin(Origins::BR);
	energy->SetPosition(size);
	energy->SetScale(4.5f, 4.5f);
	energy->sortLayer = 110;

	info = (SpriteGo*)AddGo(new SpriteGo("graphics/Cursors.ko-KR.png", "Info", "Info"));
	info->SetOrigin(Origins::TR);
	info->SetScale(4.5f, 4.5f);
	info->SetPosition(size.x, 0);
	info->sortLayer = 110;

	timeArrow = (SpriteGo*)AddGo(new SpriteGo("graphics/Cursors.ko-KR.png", "TimeArrow", "TimeArrow"));
	timeArrow->SetScale(4.5f, -4.5f);
	timeArrow->SetOrigin(Origins::TC);
	timeArrow->collider.setScale(1.f, -1.f);
	timeArrow->SetPosition(info->GetPosition().x - 225.f, info->GetPosition().y + 93.f);
	timeArrow->sortLayer = 111;
	

	energyBar.setSize(sf::Vector2f(26.f, 1.f));
	energyBar.setOrigin(energyBar.getSize().x / 2, energyBar.getSize().y);
	energyBar.setPosition(energy->GetPosition());
	energyBar.setFillColor(sf::Color::Green);

	
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
	walls.push_back(house->GetCollider()); 
	walls.push_back(shop->GetCollider()); 
	walls.push_back(shopCounter1->GetCollider()); 
	walls.push_back(shopMid1->GetCollider()); 
	walls.push_back(shopMid2_1->GetCollider()); 
	walls.push_back(shopMid2_2->GetCollider()); 
	walls.push_back(shopMid3_1->GetCollider()); 
	walls.push_back(shopMid3_2->GetCollider()); 
	walls.push_back(shopBox->GetCollider()); 

	for (int i = 0; i < shopWalls->Walls.size(); ++i)
	{
		walls.push_back(shopWalls->Walls[i].getGlobalBounds());
	}
	for (int i = 0; i < walls.size(); ++i)
	{
		player2->SetWallBounds(walls[i]); 
	}
	font.loadFromFile("fonts/SDMiSaeng.ttf");
	textMoney.setFont(font);
	textMin.setFont(font);
	textHour.setFont(font);
	textDay.setFont(font);

	// 김주현, 230811, uiview를 Init에서 주는 것이 더 좋아 보임. 주석처리
	//uiView.setSize(size);
	//uiView.setCenter(centerPos);

	// 김민지, 230807, 테스트용 주석처리
	//player2->SetOrigin(Origins::MC);
	//player2->SetPosition(centerPos);
	//
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	//230814, 임형준 테스트코드, 시간 구현
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
	/*if (hour < 12)
	{
		std::cout << day << "일 " << "오전 " << hour << "시 " << min << "분 " << time << "초" << std::endl;
	}
	else if (hour >= 12)
	{
		std::cout << day << "일 " << "오후 " << hour << "시 " << min << "분 " << time << "초" << std::endl;
	}*/
	arrowSpin += dt * 0.2381f;
	timeArrow->SetOrigin(Origins::BC);
	timeArrow->sprite.setRotation(arrowSpin);

	std::stringstream ss; 
	ss << player2->GetMoney();
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

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad5))
	{
		hour += 1;
	}
	// 김민지, 230807, 테스트용 주석처리
	// 김민지, 230808, 테스트용 주석해제, 플레이어 포지션 로그
	//worldView.setCenter(player2->GetPosition());
	//std::cout << player2->GetPosition().x << "," << player2->GetPosition().y << std::endl;
	//
	
	//뷰를 플레이어에 고정
	worldView.setCenter(player2->GetPosition());
	//std::cout << player2->GetPosition().x << " " << player2->GetPosition().y << std::endl;
	//임형준 테스트 코드
	

	playerBound = player2->GetCollider(); 
	mapBound = testFarmMap->GetCollider();
	
	player2->SetCollider(playerBound);

	energyBar.setSize(sf::Vector2f(26.f, player2->GetEnergy() * 0.67));
	energyBar.setPosition(energy->GetPosition().x- 26.f,energy->GetPosition().y - 10.f);
	energyBar.setOrigin(energyBar.getSize().x / 2, energyBar.getSize().y);
	//

	// 김민지, 230809, 샵내부
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Right))
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
			player2->SetPosition(-463.f, -770.f); //230814, 임형준 수정
			energy->SetActive(true);
			info->SetActive(true);
			timeArrow->SetActive(true);
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
			player2->SetPosition(419.f, 1866.f); // 포지션 임시 세팅 //230814, 임형준 수정
			energy->SetActive(true);
			info->SetActive(true);
			timeArrow->SetActive(true); 
		}
	}
	
	

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneId::Editor);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(energyBar);
	window.draw(textMoney);
	window.draw(textHour);
	window.draw(textDay);
}


VertexArrayGo* SceneGame::CreateBackGround(sf::Vector2i size, sf::Vector2f tileSize, sf::Vector2f texSize, string textureId)
{
	VertexArrayGo* background = new VertexArrayGo(textureId, "Background");
	background->vertexArray.setPrimitiveType(sf::Quads);
	background->vertexArray.resize(size.x * size.y * 4); //매개변수: 필요한 정점의 수

	sf::Vector2f startPos = { 0, 0 }; //시작 좌표
	sf::Vector2f offsets[4] =
	{
		//정점의 좌표
		{0.f, 0.f},
		{tileSize.x, 0.f},
		{tileSize.x, tileSize.y},
		{0.f, tileSize.y}
	}; //정점의 순서, 순서는 제공된 레퍼런스 페이지 참조하기
	sf::Vector2f texOffsets[4] =
	{
		{0.f, 0.f},
		{texSize.x, 0.f},
		{texSize.x, texSize.y},
		{0.f, texSize.y}
	};

	sf::Vector2f currPos = startPos;
	/*외곽은 벽돌로, 내부는 나머지 3개중 1개 랜덤으로 선택하기*/
	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			int texIndex = 3;
			if (i != 0 && i != size.y - 1 && j != 0 && j != size.x - 1)
				//외곽이 아닐 때, 윗줄, 아랫줄, 왼쪽, 오른쪽 순서로 외곽 검사
			{
				texIndex = Utils::RandomRange(0, 3); //타일 3개 중 1개 랜덤으로
			}

			int tileIndex = size.x * i + j; //2차원 배열의 인덱스를 1차원 배열 인덱스로 변경
			for (int k = 0; k < 4; k++) //4각형의 정점을 하나씩 도는 for문
			{
				int vertexIndex = tileIndex * 4 + k; //정점의 인덱스
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