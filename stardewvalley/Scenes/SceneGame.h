#pragma once
#include "Scene.h"

class VertexArrayGo;
class Player2;
class SpriteGo;
class Wall;
class SliceImageGo;
class Inventory;
class RootingItem;
class QuickInventory;
class RectangleGo;
class ShopTap;
class ShopInterior;
class TileMap;
class TextGo;
class HomeInterior;
class HomeTap;
class ObjectTable;

class SceneGame : public Scene
{
protected:
	int stoneCount = 0;
	VertexArrayGo* background;
	sf::FloatRect wallBounds;

	bool enterShop = false;
	bool enterHome = false;
	
	Player2* player2;

	// �ӽ� ��
	TileMap* testFarmMap;
	TileMap* testFarmMap2;
	TileMap* testFarmMapObj;
	//SpriteGo* testFarmMap; // ���� ���
	SpriteGo* houseExterior; // �� �ܺ�
	SpriteGo* shopExterior; // �� �ܺ�

	//오브젝트테이블
	ObjectTable* Objtable;


	ShopTap* shopTap;
	HomeTap* homeTap;

	ShopInterior* shopInterior;
	HomeInterior* homeInterior;
	SpriteGo* bedding;

	// INGAME UI
	SpriteGo* energy;
	SpriteGo* info;
	SpriteGo* timeArrow;
	float arrowSpin = 0.f;
	RectangleGo* energyBar; 
	int energys;
	TextGo* texMoney;
	TextGo* texMin;
	TextGo* texHour;
	TextGo* collon;
	TextGo* texDay;
	TextGo* dayday;

	float time = 0.f;
	int min = 0;
	int hour = 6;
	int day = 1;

	std::vector<sf::FloatRect> walls;
	sf::FloatRect playerBound; 
	sf::FloatRect mapBound;

	Inventory* inven;
	std::list<RootingItem*>rootingItems; 
	QuickInventory* quickinven;

	bool off = false;
	bool once = false;

	sf::Vector2f tileSize;
	sf::Vector2f shopPos = { 9.f, 16.f };
	sf::Vector2f housePos = { 21.f, 16.f };

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

	void SpawnRootingItem(ItemId id);
};

