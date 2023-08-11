#include "stdafx.h"
#include "SceneEditor.h"
#include "Framework.h"
#include "UiButton.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include "TileMap.h"
#include "RectangleGo.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "TextGo.h"

SceneEditor::SceneEditor()
	:Scene(SceneId::Editor)
{
	resourceListPath = "scripts/defaultResourceList.csv";
}

void SceneEditor::Init()
{
	Release();

	auto size = FRAMEWORK.GetWindowSize();
	centerPos = size * 0.5f;

	buttonCreate = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "ok", "ok"));

	//buttonCreate->sprite.setScale(2.0f, 2.0f);
	buttonCreate->SetOrigin(Origins::TL);
	buttonCreate->sortLayer = 101;
	buttonCreate->OnClick = [this]()
	{
		cout << "OnClick" << endl;
		if (farmMap != nullptr)
		{
			RemoveGo(farmMap);
			delete farmMap;
			farmMap = nullptr;
		}
		
		farmMap = (TileMap*)AddGo(new TileMap("map/spring_outdoorsTileSheet.png", "dirtTile"));
		farmMap->Reset();
		farmMap->Load(col, row, 48.f, 96.f);
		farmMap->SetOrigin(Origins::MC);
		farmMap->SetPosition(centerPos.x + 500.f, centerPos.y);

		MapLT = { farmMap->vertexArray.getBounds().left, farmMap->vertexArray.getBounds().top };
		MapSize = farmMap->GetTileMapSize();
		farmMap->sortLayer = -1;

		//worldView.setCenter(farmMap->GetPosition());

		//cout << MapLT.x << ", " << MapLT.y << endl;
	};
	
	buttonRowUp = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowUp", "arrowUp"));
	buttonRowUp->SetOrigin(Origins::MC);
	buttonRowUp->sortLayer = 101;

	buttonRowDown = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowDown", "arrowDown"));
	buttonRowDown->SetOrigin(Origins::MC);
	buttonRowDown->sortLayer = 101;

	buttonColUp = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowUp", "arrowUp"));
	buttonColUp->SetOrigin(Origins::MC);
	buttonColUp->sortLayer = 101;

	buttonColDown = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowDown", "arrowDown"));
	buttonColDown->SetOrigin(Origins::MC);
	buttonColDown->sortLayer = 101;

	selectTile = (SpriteGo*)AddGo(new SpriteGo("map/spring_outdoorsTileSheet_cut1.png", "selectTile"));
	selectTile->SetOrigin(Origins::TL);
	selectTile->SetActive(false);
	selectTile->sortLayer = 3;
	//sellectTile->sortLayer = 100;

	numUI = (SpriteGo*)AddGo(new SpriteGo("graphics/numUI.png", "numUI"));
	numUI->SetOrigin(Origins::ML);

	palletBg = (TileMap*)AddGo(new TileMap("map/walls_and_floors.png", "palletBg")); 
	palletBg->setTexSize(32.f, 32.f);
	palletBg->setTilesize(96.f, 96.f);
	palletBg->Load(7, 20, 64.f, 528.f);
	palletBg->SetOrigin(Origins::TL);
	palletBg->SetPosition(0, 0);
	palletBg->sortLayer = 100;

	std::unordered_map<int, int>;
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

	auto size = FRAMEWORK.GetWindowSize();
	centerPos = size * 0.5f;

	worldView.setSize(size);
	worldView.setCenter(centerPos);
	WVcenterPos = centerPos;

	uiView.setSize(size);
	uiView.setCenter(centerPos);

	buttonCreate->SetPosition(20.f, 20.f);

	buttonRowUp = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowUp", "arrowUp"));
	buttonRowUp->SetOrigin(Origins::MC);
	buttonRowUp->sortLayer = 101;

	buttonRowDown = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowDown", "arrowDown"));
	buttonRowDown->SetOrigin(Origins::MC);
	buttonRowDown->sortLayer = 101;

	buttonColUp = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowUp", "arrowUp"));
	buttonColUp->SetOrigin(Origins::MC);
	buttonColUp->sortLayer = 101;

	buttonColDown = (UiButton*)AddGo(new UiButton("graphics/Cursors.ko-KR.png", "arrowDown", "arrowDown"));
	buttonColDown->SetOrigin(Origins::MC);
	buttonColDown->sortLayer = 101;
}

void SceneEditor::Exit()
{
	Scene::Exit();
}

void SceneEditor::Update(float dt)
{
	Scene::Update(dt);

	sf::Vector2f mousePosition = INPUT_MGR.GetMousePos();
	sf::Vector2f worldMousPos = ScreenToWorldPos(mousePosition);

	//cout << mousePosition.x << "," << mousePosition.y << endl;
	
	if (worldMousPos.x >= MapLT.x && worldMousPos.x <= MapLT.x + MapSize.x
		&& worldMousPos.y >= MapLT.y && worldMousPos.y <= MapLT.y + MapSize.y)
	{
		int tileX = static_cast<int>((worldMousPos.x - MapLT.x) / tilesize.x);
		int tileY = static_cast<int>((worldMousPos.y - MapLT.y) / tilesize.y);

		//cout << tileX << ", " << tileY << endl;
		selectTile->SetPosition({ tileX * tilesize.x + MapLT.x, tileY * tilesize.y + MapLT.y });
		//auto tile = farmMap->tiles[tileY * row + tileX];
	}

	//230810, 윤유림, 마우스로 월드 뷰 이동
	{
		direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
		direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);

		float magnitude = Utils::Magnitude(direction);
		if (magnitude > 1.f)
		{
			direction /= magnitude;
		}

		WVcenterPos += direction * 300.f * dt;
		worldView.setCenter(WVcenterPos);
	}
	//

}

void SceneEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
