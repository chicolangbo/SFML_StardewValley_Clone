#pragma once
#include "Scene.h"

class VertexArrayGo;
class Player2;
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
	
	//������ �׽�Ʈ
	SpriteGo* energy;
	SpriteGo* info;
	sf::RectangleShape energyBar;
	int energys;
	//sf::FloatRect houseBound; 
	std::vector<sf::FloatRect> walls;
	sf::FloatRect playerBound; 
	sf::FloatRect mapBound;
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

