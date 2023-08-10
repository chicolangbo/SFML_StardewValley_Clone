#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "SceneEditor.h"
#include "DataTableMgr.h"
#include "StringTable.h"

void SceneMgr::Init()
{
	if (!scenes.empty())
	{
		Release();
	}

	//230808, À±À¯¸², ¿¡µðÅÍ ¾À Ãß°¡

	//
	scenes.push_back(new SceneGame());
	scenes.push_back(new SceneEditor());

	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentSceneId = startSceneId;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter();
}

void SceneMgr::Release()
{
	if (scenes.empty())
	{
		return;
	}

	for (auto scene : scenes)
	{
		//scene->Release();
		delete scene;
	}
	scenes.clear();

	currentSceneId = SceneId::None;
	currentScene = nullptr;
}

void SceneMgr::UpdateEvent(float dt)
{
	currentScene->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	currentScene->Draw(window);
}

void SceneMgr::ChangeScene(SceneId id)
{
	currentScene->Exit();
	currentSceneId = id;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter();
}

Scene* SceneMgr::GetCurrScene() const
{
	return currentScene;
}
