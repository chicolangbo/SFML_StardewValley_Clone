#pragma once
#include "Scene.h"

class VertexArrayGo;
class Player2;
class SpriteGo;
class Wall;
class SliceImageGo;
class Inventory;

class SceneGame : public Scene
{
protected:
	VertexArrayGo* background;
	sf::FloatRect wallBounds;
	// ±è¹ÎÁö, 230809, Ãß°¡
	bool enterShop = false;
	//

	Player2* player2;
	// ±è¹ÎÁö, 230809, Ãß°¡
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
	//ÀÓÇüÁØ Å×½ºÆ®
	float totalRotation=0.f;
	bool axeRotation = false;

	// ±è¹ÎÁö, 230810, 9slice Å×½ºÆ® Ãß°¡
	SliceImageGo* test;
	//

	// ±è¹ÎÁö, 230811, ÀÎº¥Åä¸® Ãß°¡
	Inventory* inven;
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
};

