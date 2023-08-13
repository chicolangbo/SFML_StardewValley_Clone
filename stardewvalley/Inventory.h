#pragma once
#include "Item.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include "SliceImageGo.h"
#include "UiButton.h"
#include "TextGo.h"

class Player2;

enum class UiType
{
	COMMON,
	BOX,
	LINE,
	BUTTON,
	ITEM,
	MAP,
	MAKE,
	CHANEGE
};

class Inventory : public GameObject
{
private:
	std::unordered_map<std::string, tagItemInfo> playerItemMap;

	int itemCapacity = 36;
	int curFundsInt = 0; // 현재 소지금
	int totalEarningsInt = 0; // 총합 자금

	std::multimap<UiType, GameObject*> invenUiObjects; // 멀티맵으로 ui오브젝트 탐색(키 중복 가능)

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
	std::vector<SpriteGo> cell;
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
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	void SetItemWindow();
	void SetMapWindow();
	void SetMakeWindow();
	void SetChangeSceneWindow();
	void SetWindowClear();

	void ButtonSetUp();
	void SetPlayer(Player2* p);
};