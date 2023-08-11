#pragma once
#include "Item.h"
#include "GameObject.h"
#include "UiButton.h"

class Player2;

class Inventory : public GameObject
{
private:
	std::vector<tagItemInfo> allItem;
	std::vector<tagItemInfo> item; // 플레이어가 가진 아이템
	std::vector<tagItemInfo>::iterator itemI;

	Player2* player;

	tagItemInfo equip;

public:
	Inventory();
	~Inventory();

	int ShowInventory();

	void addItem(tagItemInfo item);

	tagItemInfo SellItem(const int num, int& gold);
	void EquipItem(const int num);

	tagItemInfo GetEquipment()const { return equip; }
	void SetEquipment(tagItemInfo& e) { equip = e; }
	void SetPlayer(Player2* p) { player = p; }


};