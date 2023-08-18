#include "stdafx.h"
#include "SceneTitle.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include "Framework.h"
#include "VertexArrayGo.h"
#include "UiButton.h"
#include "TextGo.h"
#include "SliceImageGo.h"
#include "DataTableMgr.h"

SceneTitle::SceneTitle()
{
	resourceListPath = "scripts/defaultResourceList.csv";
}

void SceneTitle::Init()
{
	Release();

	sf::Vector2f size = FRAMEWORK.GetWindowSize(); 
	worldView.setSize(size * 0.5f); 
	worldView.setCenter(0, 0);
	uiView.setSize(size);
	uiView.setCenter(0,0);

	titleBg = (SpriteGo*)AddGo(new SpriteGo("graphics/sky.png", "sky", "sky"));
	titleBg->SetScale(2.f, 3.f);
	titleBg->SetOrigin(Origins::MC);     
	titleBg->SetPosition(0.f, -350.f); 

	mountBack = (SpriteGo*)AddGo(new SpriteGo("graphics/Cursors.ko-KR.png", "mount2", "mount2"));
	mountBack->SetScale(1.5f, 1.5f);
	mountBack->SetOrigin(Origins::MC);
	mountBack->SetPosition(0.f, 90.f);

	mountFront = (SpriteGo*)AddGo(new SpriteGo("graphics/Cursors.ko-KR.png", "mount1", "mount1"));
	mountFront->SetScale(1.5f, 1.5f);
	mountFront->SetOrigin(Origins::MC);
	mountFront->SetPosition(0.f, 160.f);

	bush = (SpriteGo*)AddGo(new SpriteGo("graphics/Clouds.png", "bush", "bush"));
	bush->SetScale(1.9f, 1.5f);
	bush->SetOrigin(Origins::MC);
	bush->SetPosition(0.f, 160.f);

	logo = (SpriteGo*)AddGo(new SpriteGo("graphics/TitleButtons.ko-KR.png", "logo", "logo")); 
	logo->SetOrigin(Origins::MC);   
	logo->SetPosition(0,-1000.f); 

	start = (UiButton*)AddGo(new UiButton("graphics/TitleButtons.ko-KR.png","newGame1","newGame1")); 
	start->SetOrigin(Origins::TL); 
	start->SetPosition(-390.f,30.f); 
	start->SetScale(2.f,2.f);  
	start->sortLayer = 100; 
	start->SetActive(false);

	exit = (UiButton*)AddGo(new UiButton("graphics/TitleButtons.ko-KR.png", "exit1", "exit1")); 
	exit->SetOrigin(Origins::TL); 
	exit->SetPosition(250.f,30.f); 
	exit->SetScale(2.f, 2.f); 
	exit->sortLayer = 100; 
	exit->SetActive(false);

	start->OnClick = [this]()
	{
		SCENE_MGR.ChangeScene(SceneId::Game); 
	};

	exit->OnClick = [this]()
	{
		window.close();
	};

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneTitle::Enter()
{
	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt) 
{
	Scene::Update(dt);
	float logoPos = logo->GetPosition().y;
	logoPos += dt * 300.f;
	if (logoPos <= -100.f)
	{
		logo->SetPosition(0, logoPos);
	}
	else
	{
		time += dt;
		if (time >= 0.5f && !start->GetActive())
		{

			start->SetActive(true);
		}
		if (time >= 1.f && !exit->GetActive())
		{
			exit->SetActive(true);
		}
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window); 
	//window.draw(start->sprite);
	
}

void SceneTitle::ShowStartButton()
{
	start = (UiButton*)AddGo(new UiButton("graphics/TitleButtons.ko-KR.png", "newGame1", "newGame1"));
	start->SetOrigin(Origins::TL);
	start->SetPosition(-390.f, 30.f);
	start->SetScale(2.f, 2.f);
	start->sortLayer = 100;

	start->OnClick = [this]()
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	};
}

void SceneTitle::ShowExitButton()
{
	exit = (UiButton*)AddGo(new UiButton("graphics/TitleButtons.ko-KR.png", "exit1", "exit1"));
	exit->SetOrigin(Origins::TL);
	exit->SetPosition(250.f, 30.f);
	exit->SetScale(2.f, 2.f);
	exit->sortLayer = 100;

	exit->OnClick = [this]()
	{
		window.close();
	};
}
