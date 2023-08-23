#pragma once
#include "Scene.h"
#include "Item.h"
#include "ObjectPool.h"

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
class Parsnip;
class Potato;
class Cauliflower;

struct DataLoad
{
	std::list<tagItemInfo> pl_ItemList;
	int pl_totalMoney;
	int pl_money;
	int pl_energy;
	int game_min;
	int game_hour;
	int game_day;
};

class SceneGame : public Scene
{
protected:
	// PLAYER COLLIDE
	Player2* player2;
	std::vector<sf::FloatRect> walls;
	std::vector<sf::FloatRect> farmWalls;
	std::vector<sf::FloatRect> shopWalls;
	std::vector<sf::FloatRect> houseWalls;

	sf::FloatRect playerBound;
	sf::FloatRect mapBound;

	// DATA SAVE & LOAD
	DataLoad lData;
	DataLoad sData;

	// OBJECT
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

	// HOE DIRT
	vector<HoeDirt*> tempDirt;
	HoeDirt* dirt;
	vector<vector<HoeDirt*>> dirtArray;
	SpriteGo* selectTile; //red or green box
	bool canPlant = false;

	// FARM MAP
	TileMap* testFarmMap;
	TileMap* testFarmMap2;
	TileMap* testFarmMapObj;
	SpriteGo* shopExterior;
	sf::Vector2f mapLT;
	sf::Vector2f tileSize;
	int col = 0;
	int row = 0;

	// CROP POOL
	ObjectPool<Parsnip> parsnipPool;
	ObjectPool<Potato> potatoPool;
	ObjectPool<Cauliflower> cauliflowerPool;

	// HOME, SHOP
	Location location = Location::Home;
	sf::RectangleShape homeExit;
	sf::RectangleShape shopExit;
	bool enterShop = false;
	bool enterHome = false;
	bool init = false;
	ShopTap* shopTap;
	HomeTap* homeTap;
	ShopInterior* shopInterior;
	HomeInterior* homeInterior;
	SpriteGo* houseExterior;
	SpriteGo* bedding;
	sf::Vector2f playerSpwan = { 606.f, 653.f };
	sf::Vector2f shopPos = { 9.f, 16.f };
	sf::Vector2f housePos = { 21.f, 16.f };
	sf::Vector2f houseInEnter = { 193.f, 728.f };
	sf::Vector2f shopInEnter = { 416.f, 1882.f };
	sf::Vector2f houseOutEnter = { 207.f, -424.f };
	sf::Vector2f shopOutEnter = { -642.f, -282.f };

	// INGAME UI
	SpriteGo* energy;
	SpriteGo* info;
	SpriteGo* timeArrow;
	RectangleGo* energyBar;
	TextGo* texMoney;
	TextGo* texMin;
	TextGo* texHour;
	TextGo* collon;
	TextGo* texDay;
	TextGo* dayday;
	float arrowSpin = 0.f;
	int energys;
	float time = 0.f;
	int min = 0;
	int hour = 6;
	int day = 1;

	// INVEN & ITEMS
	Inventory* inven;
	std::list<RootingItem*>rootingItems;
	QuickInventory* quickinven;
	bool off = false;
	bool once = false;

	//test
	RectangleGo* testbox;
	//RectangleGo* night; 
	
public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SpawnRootingItem(ItemId id, sf::Vector2f pos);
	void SetAct(bool is);

	void HitStone(int x, int y);
	void HitTimber(int x, int y);
	void HitTree(int x, int y);
	void HitWeed(int x, int y);

	bool HasObjectAt(int x, int y);
	void SetGreenTile();

	void PlantParsnip(int x, int y);
	void PlantPotato(int x, int y);
	void PlantCauli(int x, int y);

	int GetDay() { return day; }

	void ChangeDate();

	template <typename T>
	void ClearObjectPool(ObjectPool<T>& pool);
};

template<typename T>
inline void SceneGame::ClearObjectPool(ObjectPool<T>& pool)
{
	for (auto obj : pool.GetUseList())
	{
		RemoveGo(obj);
	}
	pool.Clear();
}