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
	LINE,
	BUTTON,
	ITEM,
	TOOL,
	MAP,
	MAKE,
	CHANEGE
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
	~Inventory();

	//void AddPlayerItem(std::string name);
	GameObject* AddUi(GameObject* go);
	bool Exist(GameObject* go);

	virtual void Init();
	virtual void Reset();
	virtual void Release();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	void SetItemWindow();
	void SetMapWindow();
	void SetMakeWindow();
	void SetChangeSceneWindow();
	void SetWindowClear();

	void ItemIconSetUp();
	void ButtonSetUp();
	void PlayerInfoUpdate();
	void IconUpdate();

	void SetPlayer(Player2* p);
	void SetPlayerItemList() { playerItemList = player->GetPlayerItemList(); }
	int GetItemCapacity() { return itemCapacity; }
	void SortGos();
};