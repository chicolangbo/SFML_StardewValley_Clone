#pragma once
#include "Item.h"
#include "GameObject.h"
#include "Player2.h"
#include "SpriteGo.h"
#include "SliceImageGo.h"
#include "UiButton.h"

class Inventory;
class Slot;
//얘도 플레이어에서 다이렉트로 받아오는걸로 수정
class QuickInventory : public GameObject
{
protected:
	std::list<GameObject*> quickinvenUi;//얘를 통해서 그림
	SliceImageGo quickInven;
	SpriteGo mark;

	std::list<tagItemInfo>* playerItemList;
	std::unordered_map<ItemId, SpriteGo> itemIconList;

	std::vector<Slot*>* quickslot;//포인터로 들고온애
	Slot* mouse;
	std::vector<Slot*> quickslots;
	ItemId itemid;

	Player2* player;

	bool off = false;

public:
	QuickInventory(const std::string& n = "");
	~QuickInventory();

	GameObject* AddUi(GameObject* go); 
	bool Exist(GameObject* go); 

	virtual void Init();
	virtual void Reset();
	virtual void Release();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window); 

	void SetQuickSlot(std::vector<Slot*>* s){quickslot = s;}
	void SetPlayer(Player2* p) { player = p; }
	void SetPlayerItemList() { playerItemList = player->GetPlayerItemList(); }

	void IconUpdate();
	void ItemIconSetUp();

	ItemId GetItemId() { return itemid; } 
	
};

