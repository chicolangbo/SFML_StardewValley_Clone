#pragma once
#include "Scene.h"

class UiButton;
class TileMap;
class RectangleGo;
class TextGo;
class SpriteGo;
class StringTable;

struct Collider
{
	int indexX;
	int indexY;
};

struct Object
{
	int indexX;
	int indexY;
	float left;
	float top;
	float width;
	float height;
	ObjType type;
};

class SceneEditor : public Scene
{
protected:

	//좌표
	sf::Vector2f centerPos;
	sf::Vector2f WVcenterPos;

	//맵
	TileMap* farmMapT1 = nullptr;
	TileMap* farmMapT2 = nullptr;
	TileMap* farmMapObj = nullptr;
	TileMap* farmMapColl = nullptr;
	TileMap* selectMap = nullptr;

	sf::Vector2f MapLT;
	sf::Vector2f MapSize;
	sf::Vector2f tilesize = { 72.f, 72.f };

	SpriteGo* selectTile; //레이어 1,2
	SpriteGo* selectObj; //오브젝트 레이어
	SpriteGo* curTile;

	RectangleGo* selColl; //충돌체
	
	//팔레트
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

	UiButton* buttonSave;
	UiButton* buttonLoad;

	SpriteGo* numUI;
	TextGo* colText;
	TextGo* rowText;

	TextGo* Layer1;
	TextGo* Layer2;
	TextGo* LayerObj;
	TextGo* LayerColl;

	TextGo* saveText;
	TextGo* loadText;

	TextGo* nowLayer;
	sf::Vector2f direction;
	int currentLayer;
	
	int col = 38;
	int row = 41;

	StringTable* stringTable = nullptr;

	//충돌체
	std::vector<RectangleGo*> colliders;
	std::vector<Collider> tempcolliders;
	bool IsCollActive = false;

	//오브젝트
	std::vector<Object> objects;

	sf::Vector2f tileScale = { 4.5f, 4.5f };

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
	bool SaveCollider(const string& filePath);
	bool LoadCollider(const string& filePath);
	void SetColliders();
	string GetCurrentLayer();
	ObjType GetObjType(sf::IntRect rect);
	void AddObject(int indexX, int indexY, sf::IntRect rect, ObjType type);
	bool SaveObject(const std::string& filePath);
	bool LoadObject(const std::string& filePath);

	bool IsObjectAdded(int indexX, int indexY, ObjType type);
	
};

