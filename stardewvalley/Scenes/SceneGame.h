#pragma once
#include "Scene.h"

class VertexArrayGo;
class Player2;
class SpriteGo;
class Wall;
class SliceImageGo;
class Inventory;
class RootingItem;

class SceneGame : public Scene
{
protected:
	VertexArrayGo* background;
	sf::FloatRect wallBounds;
	// 김민지, 230809, 추가
	bool enterShop = false;
	//

	Player2* player2;
	// 김민지, 230809, 추가
	SpriteGo* testFarmMap;
	SpriteGo* house;
	SpriteGo* shop;
	SpriteGo* shopInside;
	SpriteGo* pierre;
	SpriteGo* robin;
	SpriteGo* shopCounter1;
	SpriteGo* shopCounter2;
	SpriteGo* shopMid1;
	SpriteGo* shopMid2_1;
	SpriteGo* shopMid2_2;
	SpriteGo* shopMid3_1;
	SpriteGo* shopMid3_2;
	SpriteGo* shopBox;
	Wall* homeWalls;
	Wall* shopWalls;
	//
	//Farmer* player;
	//임형준 테스트
	float totalRotation=0.f;
	bool axeRotation = false;

	// 김민지, 230811, 인벤토리 추가
	Inventory* inven;
	std::list<RootingItem*>rootingItems; // 플레이어-오브젝트 상호작용 시 필드에 생기는 아이템
	//
public:
	SceneGame();
	virtual ~SceneGame() override = default;

	VertexArrayGo* CreateBackGround(sf::Vector2i size, sf::Vector2f tileSize, sf::Vector2f texSize, string textureId);

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	// 김민지, 230815, 플레이어-오브젝트 상호작용시 아이템 스폰하는 함수 추가
	void SpawnRootingItem(ItemId id);
};

