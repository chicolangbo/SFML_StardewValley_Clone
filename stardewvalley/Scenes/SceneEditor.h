#pragma once
#include "Scene.h"

class UiButton;
class TileMap;
class RectangleGo;
class TextGo;
class SpriteGo;
class StringTable;

class SceneEditor : public Scene
{
protected:

	//ÁÂÇ¥
	sf::Vector2f centerPos;
	sf::Vector2f WVcenterPos;

	//¸Ê
	TileMap* farmMapT1 = nullptr;
	TileMap* farmMapT2 = nullptr;
	TileMap* farmMapObj = nullptr;
	TileMap* farmMapColl = nullptr;
	TileMap* selectMap = nullptr;

	sf::Vector2f MapLT;
	sf::Vector2f MapSize;
	sf::Vector2f tilesize = { 48.f, 48.f };

	SpriteGo* selectTile;
	SpriteGo* selectObj;
	SpriteGo* curTile;
	
	//ÆÈ·¹Æ®
	SpriteGo* tilePallet;
	SpriteGo* ObjPallet;

	SpriteGo* selPallet;

	RectangleGo* selPalTile;

	sf::Vector2f texTileSize = { 16.f, 16.f };
	sf::Vector2f palletTileSize = { 48.f, 48.f };
	sf::Vector2f palletLT;
	sf::Vector2f palletSize;
	sf::Vector2f palletTexSize = { 192.f, 112.f };
	int palNumX = 0;
	int palNumY = 0;

	UiButton* buttonPalL;
	UiButton* buttonPalR;
	int palNum = 1;

	//UI
	TileMap* palletBg = nullptr;

	UiButton* buttonCreate;
	UiButton* buttonRowUp;
	UiButton* buttonRowDown;
	UiButton* buttonColUp;
	UiButton* buttonColDown;

	UiButton* buttonLayer1;
	UiButton* buttonLayer2;
	UiButton* buttonLayerObj;
	UiButton* buttonLayerColl;

	SpriteGo* numUI;
	TextGo* colText;
	TextGo* rowText;

	TextGo* Layer1;
	TextGo* Layer2;
	TextGo* LayerObj;
	TextGo* LayerColl;

	sf::Vector2f direction;
	
	int col = 20;
	int row = 20;

	StringTable* stringTable = nullptr;

public:
	SceneEditor();
	virtual ~SceneEditor() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void ChangePallet();
};

