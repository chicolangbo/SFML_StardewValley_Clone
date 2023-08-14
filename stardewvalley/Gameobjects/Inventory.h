#pragma once
#include "Item.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include "SliceImageGo.h"
#include "UiButton.h"
#include "TextGo.h"

class Player2;
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
	//std::unordered_map<std::string, tagItemInfo> playerItemMap; // 이걸 플레이어로 옮기고, 벡터로 변경
	// 아이템리스트 벡터 포인터
	std::vector<tagItemInfo>* playerItemList;
	
	// 슬롯클래스 벡터 포인터
	std::vector<Slot*> slot;

	int itemCapacity = 36;
	int curFundsInt = 0; // 현재 소지금
	int totalEarningsInt = 0; // 총합 자금

	std::multimap<UiType, GameObject*> invenUiObjects; // 멀티맵으로 ui오브젝트 탐색(키 중복 가능) // 얘도 순서 있는 벡터로 바꿔주기... 

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
	sf::Vector2f cellPos;
	SliceImageGo invenBox;
	SliceImageGo invenLine;
	std::vector<SpriteGo*> cell;
	SpriteGo mapImage;
	SpriteGo ring;
	SpriteGo shoes;
	SpriteGo hat;
	SpriteGo charBg;
	TextGo curFunds;
	TextGo curFundsValue;
	TextGo totalEarnings;
	TextGo totalEarningsValue;

	tagItemInfo currentEquip;

public:
	Inventory(const std::string& n = "");
	~Inventory();

	void AddPlayerItem(std::string name);
	GameObject* AddUi(UiType t, GameObject* go);
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

	void ButtonSetUp();
	void SetPlayer(Player2* p);
	void SetPlayerItemList(std::vector<tagItemInfo>* itemList) { playerItemList = itemList; }
};