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
class Stone;
class Timber;
class Weed;
class Tree;
class HoeDirt;

class SceneGame : public Scene
{
protected:
	
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

	//object
	ObjectTable* Objtable;
	vector<Stone*> stones;
	vector<Timber*> timbers;
	vector<Weed*> weeds;
	vector<Tree*> trees;

	int stoneCount = 0;
	int timberCount = 0;
	int weedCount = 0;
	int treeCount = 0;

	string branchNick;
	string branchId;

	//hoe dirt
	HoeDirt* dirt;


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

	//test
	sf::RectangleShape testbox;

public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SpawnRootingItem(ItemId id);
	void SetAct(bool is);
};

