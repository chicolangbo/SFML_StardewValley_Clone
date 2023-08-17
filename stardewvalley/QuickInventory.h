#pragma once
#include "Item.h"
#include "GameObject.h"
#include "Player2.h"
#include "SpriteGo.h"
#include "SliceImageGo.h"
#include "UiButton.h"

class Inventory;
class Slot;

class QuickInventory : public GameObject
{
protected:
	std::list<GameObject*> quickinvenUi;//�긦 ���ؼ� �׸�
	SliceImageGo quickInven;
	SpriteGo mark;

	std::vector<Slot*>* quickslot;//�����ͷ� ����¾�
	std::vector<Slot*> quickslots;
	ItemId itemid;

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
	ItemId GetItemId() { return itemid; } 
	
};
