#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "Scene.h"
#include "Axe.h"
#include "Pickax.h"
#include "Hoe.h"
#include "Scythe.h"
#include "Wateringcan.h"
#include "Item.h"
#include "Slot.h"

class RootingItem;
class Inventory;
class SpriteGo; 

class Player2 : public SpriteGo
{
public:
	struct ClipInfo
	{
		std::string idle;
		std::string move;
		bool flipX = false;
		sf::Vector2f point;
	};

	struct HandOnItem
	{
		std::string idleItem;
		std::string moveItem;
		bool flipX = false;
		sf::Vector2f point;
	};

	struct ItemIcoinInfo
	{
		string textureId;
		string name;
		string nickName;
	};
	bool move = true;

protected:
	bool harvest = false;
	AnimationController animation;
	Axe axe;
	Pickax pickax;
	Hoe hoe;
	Scythe scythe;
	Wateringcan watering;

	SpriteGo* handitem = nullptr;
	std::unordered_map<ItemId, ItemIcoinInfo> itemIconList;

	sf::Vector2f direction;
	float speed = 500.f;

	bool filpX = false;
	bool notherItem = true;
	//bool isGround = true;

	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;

	std::vector<HandOnItem> clipInfosItem;
	HandOnItem currentClipInfoItem;

	ItemId item;

	int maxEnergy = 270;
	int energy = 270;
	int money = 500;
	int tempMoney = 0;
	int totalEarningsInt = 500;

	std::vector<sf::FloatRect> wallBounds;
	std::vector<sf::Vector2f> wallBoundsLT;
	std::vector<sf::Vector2f> wallBoundsRB;

	sf::FloatRect playerBound;

	bool playerDie = false;
	bool playingAnimation = false;
	bool one = true;
	bool boundwall = false;

	std::list<tagItemInfo> playerItemList;
	std::list<RootingItem*>*rootingItemList;

	Inventory* inven;

	sf::Vector2i playerTileIndex;
	sf::Vector2i mouseTileIndex;


public:
	bool load = false;
	//플레이어 포지션 / 타일 한칸의 사이즈 == 2차원 배열의 인덱스?
	Player2(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Player2() override { Release(); }

	void Harvest() { harvest = true; }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	bool GetFlipX() const;
	void SetFlipX(bool filp);

	int GetEnergy() { return energy; }
	int* GetMoney() { return &money; }
	int* GetTempMoney() { return &tempMoney; }

	void SetWallBounds(const sf::FloatRect& bounds);
	void ClearWalls();
	void SetCollider(const sf::FloatRect& coll);
	void SetInventory(Inventory* i) { inven = i; }

	AnimationController GetAnimation() { return animation; }

	std::list<tagItemInfo>* GetPlayerItemList() { return &playerItemList; }
	void LoadData(std::list<tagItemInfo> loadI, int loadTM, int loadM, int loadE);
	int* GetTotalEarningsInt() { return &totalEarningsInt; }
	void AddRootingItem();
	void AddPlayerItem(ItemId id);
	bool RemovePlayerItem(ItemId id);
	void SetRootingItems(std::list<RootingItem*>* r) { rootingItemList = r; }
	void MoneyUpdate();
	void SetItemId(ItemId id) { item = id; }
	void ZeroEnergy() { energy = 0; }
	sf::Vector2f GetDirection() { return direction; }
	void SetDirection(sf::Vector2f f) { direction = f; }
	ItemId GetPlayerItemId() { return item; } 
	void SetMPIndex(sf::Vector2i p, sf::Vector2i m) { playerTileIndex = p; mouseTileIndex = m; }
	void ItemIconSetUp();
	int GetItemCount();
};

