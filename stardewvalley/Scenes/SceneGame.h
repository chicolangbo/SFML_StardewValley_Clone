#pragma once
#include "Scene.h"

class VertexArrayGo;
class Player;
class Player2;
class Farmer;

class SceneGame : public Scene
{
protected:
	VertexArrayGo* background;
	sf::FloatRect wallBounds;

	//Player* player;
	Player2* player2;
	Farmer* player;
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

