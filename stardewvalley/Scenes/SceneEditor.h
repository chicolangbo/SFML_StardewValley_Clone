#pragma once
#include "Scene.h"

class UiButton;
class TileMap;
class RectangleGo;

class SceneEditor : public Scene
{
protected:

	sf::Vector2f centerPos;
	sf::Vector2f WVcenterPos;
	UiButton* buttonCreate;
	TileMap* farmMap = nullptr;
	RectangleGo* sellectTile;
	sf::Vector2f tilesize = { 48.f, 48.f };
	sf::Vector2f MapLT;
	sf::Vector2f MapSize;
	sf::Vector2f direction;
	//sf::RectangleShape sellectTile;

	int col = 20;
	int row = 20;

	TileMap* palletBg = nullptr;
public:
	SceneEditor();
	virtual ~SceneEditor() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

