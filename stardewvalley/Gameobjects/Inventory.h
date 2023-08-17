#pragma once
#include "Item.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include "SliceImageGo.h"
#include "UiButton.h"
#include "TextGo.h"
#include "Player2.h"

class Slot;

enum class UiType
{
	COMMON,
	BOX,
	BUTTON,
	ITEM,
	TOOL,
	MAP,
	MAKE,
	CHANEGE,
	LINE
};

class Inventory : public GameObject
{
private:
	// 아이템리스트 벡터 포인터(플레이어에 있음)
	std::list<tagItemInfo>* playerItemList;
	std::unordered_map<ItemId,SpriteGo> itemIconList; // 여기서 만들어두고 slot에는 포인터만 전달
	
	// 슬롯클래스 벡터
	std::vector<Slot*> slot;
	Slot* mouseSlot;

	int itemCapacity = 36;
	int* curFundsInt; // 현재 소지금
	int* totalEarningsInt; // 총합 자금

	std::list<GameObject*> invenUiObjects;

	Player2* player;

	bool invenOnOff = false;

	// ui
	SpriteGo pl;

	UiButton bag;
	UiButton map;
	UiButton make;
	UiButton changeScene;
	UiButton xButton;
	UiButton title;
	UiButton end;

	sf::Vector2f bagPos;
	sf::Vector2f mapPos;
	sf::Vector2f makePos;
	sf::Vector2f changeScenePos;
	sf::Vector2f xButtonPos;
	sf::Vector2f slotPos;

	SliceImageGo invenBox;
	SliceImageGo invenLine;

	SpriteGo mapImage;
	SpriteGo ring;
	SpriteGo shoes;
	SpriteGo hat;
	SpriteGo charBg;

	TextGo curFunds;
	TextGo curFundsValue;
	TextGo totalEarnings;
	TextGo totalEarningsValue;

public:
	Inventory(const std::string& n = "");
	virtual ~Inventory() override;

	GameObject* AddUi(GameObject* go);
	bool Exist(GameObject* go);

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetItemWindow();
	void SetMapWindow();
	void SetMakeWindow();
	void SetChangeSceneWindow();
	void SetWindowClear();

	void ItemIconSetUp();//init할떄 한번만 아이템 아이콘 들을 전부 찍어놓음
	void ButtonSetUp();//UI버튼
	void PlayerInfoUpdate();//실시간 플레이어 돈 업데이트
	void IconUpdate();//슬롯에다 아이템 업데이트 
	void ItemIndexUpdate();//아이템 위치?

	void SortGos();
	void SetPlayer(Player2* p);
	void InitInfo();
	std::unordered_map<ItemId, SpriteGo>* GetItemIconList() {
		return &itemIconList; }
	int GetItemCapacity() { return itemCapacity; }
	std::vector<Slot*>* GetSlot() { return &slot; } 
	bool GetInvenOff() { return invenOnOff; }
};