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

	titleBg = (SpriteGo*)AddGo(new SpriteGo("graphics/sky.png", "sky", "sky"));
	titleBg->SetScale(2.f, 3.f);
	titleBg->SetOrigin(Origins::MC);     
	titleBg->SetPosition(0.f, 100.f); 

	logo = (SpriteGo*)AddGo(new SpriteGo("graphics/TitleButtons.ko-KR.png", "logo", "logo"));
	logo->SetOrigin(Origins::MC);  
	logo->SetPosition(0,-100.f);

	start = (UiButton*)AddGo(new UiButton("graphics/TitleButtons.ko-KR.png","newGame1","newGame1"));
	start->SetOrigin(Origins::MC);
	start->SetPosition(350.f,550.f);
	start->SetScale(1.5f,2.f); 

	start->OnClick = [this]()
	{
		SCENE_MGR.ChangeScene(SceneId::Game); 
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

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window); 
	window.draw(start->sprite);
}
