#include "stdafx.h"
#include "SceneEditor.h"
#include "Framework.h"
#include "UiButton.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "SpriteGo.h"

SceneEditor::SceneEditor()
{
	resourceListPath = "scripts/defaultResourceList.csv";
}

void SceneEditor::Init()
{
	Release();

	auto size = FRAMEWORK.GetWindowSize();
	centerPos = size * 0.5f;

	worldView.setSize(size);
	worldView.setCenter(centerPos);

	uiView.setSize(size);
	uiView.setCenter(centerPos);

	buttonCreate = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "ok"));

	buttonCreate->sprite.setScale(2.0f, 2.0f);
	buttonCreate->SetOrigin(Origins::TR);
	buttonCreate->sortLayer = 100;
	buttonCreate->SetPosition(size.x, 0);

	buttonCreate->OnClick = [this]()
	{
		cout << "OnClick" << endl;
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
}

void SceneEditor::Exit()
{
	Scene::Exit();
}

void SceneEditor::Update(float dt)
{
	Scene::Update(dt);
}

void SceneEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
