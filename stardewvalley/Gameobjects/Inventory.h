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
	// �����۸���Ʈ ���� ������(�÷��̾ ����)
	std::list<tagItemInfo>* playerItemList;
	std::unordered_map<ItemId,SpriteGo> itemIconList; // ���⼭ �����ΰ� slot���� �����͸� ����
	
	// ����Ŭ���� ����
	std::vector<Slot*> slot;
	Slot* mouseSlot;

	int itemCapacity = 36;
	int* curFundsInt; // ���� ������
	int* totalEarningsInt; // ���� �ڱ�

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

	void ItemIconSetUp();
	void ButtonSetUp();
	void PlayerInfoUpdate();
	void IconUpdate();
	void ItemIndexUpdate();

	void SetPlayer(Player2* p);
	void SetPlayerItemList() { playerItemList = player->GetPlayerItemList(); }
	int GetItemCapacity() { return itemCapacity; }
	void SortGos();
	std::vector<Slot*>* GetSlot() { return &slot; }
};