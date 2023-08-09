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

	// 김민지, 230808, 임시맵 코드 추가
	AddGo(new SpriteGo("map/testFarmMap.png", "testFarmMap", "testFarmMap"));
	SpriteGo* testFarmMap = (SpriteGo*)FindGo("testFarmMap");
	testFarmMap->sprite.setScale(3.f, 3.f);
	testFarmMap->SetOrigin(Origins::MC);
	testFarmMap->SetPosition(0, 0);
	AddGo(new SpriteGo("map/houses.png", "house", "house"));
	SpriteGo* house = (SpriteGo*)FindGo("house");
	house->sprite.setScale(4.f, 4.f);
	house->SetOrigin(Origins::BC);
	house->SetPosition(473, -785);
	AddGo(new SpriteGo("map/spring_town.ko-KR.png", "shop", "shop"));
	SpriteGo* shop = (SpriteGo*)FindGo("shop");
	shop->sprite.setScale(4.f, 4.f);
	shop->SetOrigin(Origins::BC);
	shop->SetPosition(-537, -785);
	AddGo(new SpriteGo("map/shopInside.png", "shopInside", "shopInside"));
	SpriteGo* shopInside = (SpriteGo*)FindGo("shopInside");
	shopInside->sprite.setScale(4.f, 4.f);
	shopInside->SetOrigin(Origins::TL);
	shopInside->SetPosition(0, 0);
	shopInside->SetActive(false);
	AddGo(new SpriteGo("graphics/Pierre.png", "pierre", "pierre"));
	SpriteGo* pierre = (SpriteGo*)FindGo("pierre");
	pierre->sprite.setScale(5.f, 5.f);
	pierre->SetOrigin(Origins::MC);
	pierre->SetPosition(244.f, 1086.f);
	pierre->SetActive(false);
	AddGo(new SpriteGo("graphics/Robin.png", "robin", "robin"));
	SpriteGo* robin = (SpriteGo*)FindGo("robin");
	robin->sprite.setScale(5.f, 5.f);
	robin->SetOrigin(Origins::MC);
	robin->SetPosition(352.f, 1086.f);
	robin->SetActive(false);

	AddGo(new SpriteGo("map/shopInside.png", "shopCounter1", "shopCounter1"));
	SpriteGo* shopCounter1 = (SpriteGo*)FindGo("shopCounter1");
	shopCounter1->sprite.setScale(4.f, 4.f);
	shopCounter1->SetOrigin(Origins::TL);
	shopCounter1->SetPosition(48.f*4, 275.f*4);
	shopCounter1->SetActive(false);
	AddGo(new SpriteGo("map/shopInside.png", "shopCounter2", "shopCounter2"));
	SpriteGo* shopCounter2 = (SpriteGo*)FindGo("shopCounter2");
	shopCounter2->sprite.setScale(4.f, 4.f);
	shopCounter2->SetOrigin(Origins::TL);
	shopCounter2->SetPosition(128.f*4, 254.f*4);
	shopCounter2->SetActive(false);

	player2 = (Player2*)AddGo(new Player2());
	//

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

	uiView.setSize(size);
	uiView.setCenter(centerPos);


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
	
	// 김민지, 230807, 테스트용 주석처리
	// 김민지, 230808, 테스트용 주석해제, 플레이어 포지션 로그
	worldView.setCenter(player2->GetPosition());
	std::cout << player2->GetPosition().x << "," << player2->GetPosition().y << std::endl;
	//
	
	//뷰를 플레이어에 고정
	worldView.setCenter(player2->GetPosition());

	// 김민지, 230809, 샵내부
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		if (enterShop)
		{
			enterShop = false;
			for (auto go : gameObjects)
			{
				go->SetActive(false);
			}
			player2->SetActive(true);
			player2->SetPosition(419.f, 1823.f);
			SpriteGo* shopInside = (SpriteGo*)FindGo("shopInside");
			SpriteGo* pierre = (SpriteGo*)FindGo("pierre");
			SpriteGo* robin = (SpriteGo*)FindGo("robin");
			SpriteGo* shopCounter1 = (SpriteGo*)FindGo("shopCounter1");
			SpriteGo* shopCounter2 = (SpriteGo*)FindGo("shopCounter2");
			shopInside->SetActive(true);
			pierre->SetActive(true);
			robin->SetActive(true);
			shopCounter1->SetActive(true);
			shopCounter2->SetActive(true);
		}
		else
		{
			enterShop = true;
			player2->SetPosition(-463.f, -845.f); // 포지션 임시 세팅
			for (auto go : gameObjects)
			{
				go->SetActive(true);
			}
			SpriteGo* shopInside = (SpriteGo*)FindGo("shopInside");
			SpriteGo* pierre = (SpriteGo*)FindGo("pierre");
			SpriteGo* robin = (SpriteGo*)FindGo("robin");
			SpriteGo* shopCounter1 = (SpriteGo*)FindGo("shopCounter1");
			SpriteGo* shopCounter2 = (SpriteGo*)FindGo("shopCounter2");
			shopInside->SetActive(false);
			pierre->SetActive(false);
			robin->SetActive(false);
			shopCounter1->SetActive(false);
			shopCounter2->SetActive(false);
		}
	}
	//
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
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