#pragma once
#include "Scene.h"

class VertexArrayGo;
class Player;
class Player2;
class Farmer;
class SpriteGo;
class Wall;

class SceneGame : public Scene
{
protected:
	VertexArrayGo* background;
	sf::FloatRect wallBounds;
	// �����, 230809, �߰�
	bool enterShop = false;
	//

	//Player* player;
	Player2* player2;
	// �����, 230809, �߰�
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

