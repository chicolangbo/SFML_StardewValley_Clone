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

	// 김민지, 230807, 테스트용 주석처리
	//sf::Vector2f tileWorldSize = { 50.f, 50.f };
	//sf::Vector2f tileTexSize = { 50.f ,50.f };
	//background = CreateBackGround({ 100, 100 }, { 50.f, 50.f }, { 50.f, 50.f }, "graphics/background_sheet.png");
	//AddGo(background);
	//player2 = (Player2*)AddGo(new Player2());
	//UiButton* button = (UiButton*)AddGo(new UiButton("graphics/TitleButtons1.png", "button"));
	//button->sprite.setScale(2.0f, 2.0f);
	//button->SetOrigin(Origins::TR);
	//button->sortLayer = 100;
	//button->SetPosition(size.x, 0);
	//button->OnEnter = [button]()
	//{
	//	cout << "Enter" << endl;
	//	sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/TitleButtons2.png");
	//	button->sprite.setTexture(*tex);
	//};
	//button->OnExit = [button]()
	//{
	//	cout << "OnExit" << endl;
	//	sf::Texture* tex = RESOURCE_MGR.GetTexture(button->textureId);
	//	button->sprite.setTexture(*tex);
	//};
	//button->OnClick = [this]()
	//{
	//	SCENE_MGR.ChangeScene(sceneId);
	//	cout << "OnClick" << endl;
	//};
	//

	// 김민지, 230807, 테스트용 추가
	player2 = (Player2*)AddGo(new Player2());
	AddGo(new SpriteGo("graphics/TitleButtons.ko-KR.png", "logo", "logo"));
	AddGo(new SpriteGo("graphics/TitleButtons.ko-KR.png", "load", "load"));
	SpriteGo* logo = (SpriteGo*)FindGo("logo");
	SpriteGo* load = (SpriteGo*)FindGo("load");
	logo->SetOrigin(Origins::MC);
	logo->SetPosition(0, 0);
	load->SetOrigin(Origins::MC);
	load->SetPosition(0, 0);
	//

	for (auto go : gameObjects)
	{
		go->Init();
	}

	//background->sortLayer = -1;
	//background->SetOrigin(Origins::MC);
	//background->SetPosition(centerPos);

	//wallBounds = background->vertexArray.getBounds();
	//

	//player->SetWallBounds(wallBounds);

	//player->sortLayer = 1;
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
	//worldView.setCenter(player2->GetPosition());
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