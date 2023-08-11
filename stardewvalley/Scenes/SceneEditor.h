#pragma once
#include "Scene.h"

class UiButton;
class TileMap;
class RectangleGo;
class TextGo;
class SpriteGo;

class SceneEditor : public Scene
{
protected:

	//ÁÂÇ¥
	sf::Vector2f centerPos;
	sf::Vector2f WVcenterPos;

	//¸Ê
	TileMap* farmMap = nullptr;

	sf::Vector2f MapLT;
	sf::Vector2f MapSize;
	sf::Vector2f tilesize = { 48.f, 48.f };

	SpriteGo* selectTile;
	//ÆÈ·¹Æ®
	

	//UI
	TileMap* palletBg = nullptr;

	UiButton* buttonCreate;
	UiButton* buttonRowUp;
	UiButton* buttonRowDown;
	UiButton* buttonColUp;
	UiButton* buttonColDown;

	SpriteGo* numUI;
	TextGo* colText;
	TextGo* rowText;

	sf::Vector2f direction;
	
	int col = 20;
	int row = 20;

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

