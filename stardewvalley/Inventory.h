#pragma once
#include "Item.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include "SliceImageGo.h"
#include "UiButton.h"

class Player2;

class Inventory : public GameObject
{
private:
	std::vector<tagItemInfo> allItem; // 데이터테이블 읽어와야 함
	std::vector<tagItemInfo> item; // 플레이어가 가진 아이템
	std::vector<tagItemInfo>::iterator itemI;

	GameObject* AddUi(GameObject* go);
	bool Exist(GameObject* go);
	std::list<GameObject*> uiObjects;
	//std::list<GameObject*> removeUiObjects;

	Player2* player;
	UiButton bag;
	UiButton map;
	UiButton make;
	UiButton changeScene;

	SliceImageGo invenBox;
	SliceImageGo invenLine;
	std::vector<SpriteGo> cell;


	tagItemInfo equip;

public:
	Inventory(const std::string& n = "");
	~Inventory();

	int ShowInventory();

	void addItem(tagItemInfo item);

	//tagItemInfo SellItem(const int num, int& gold);
	//void EquipItem(const int num);

	//tagItemInfo GetEquipment()const { return equip; }
	//void SetEquipment(tagItemInfo& e) { equip = e; }
	//void SetPlayer(Player2* p) { player = p; }

	virtual void Init();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

};