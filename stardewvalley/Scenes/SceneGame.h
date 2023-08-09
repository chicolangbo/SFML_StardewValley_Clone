#pragma once
#include "Scene.h"

class VertexArrayGo;
class Player;
class Player2;

//±Ë«Ï¡ÿ ±Ú¬¶
class Axe;

class SceneGame : public Scene
{
protected:
	VertexArrayGo* background;
	sf::FloatRect wallBounds;

	//±Ë«Ï¡ÿ ±Ú¬¶
	Axe* axe2;

	Player2* player2;
	//¿”«¸¡ÿ ≈◊Ω∫∆Æ
	float totalRotation=0.f;
	bool axeRotation = false;
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

