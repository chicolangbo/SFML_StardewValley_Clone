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
	std::vector<tagItemInfo> allItem; // 데이터테이블 읽어와야 함
	std::vector<tagItemInfo> item; // 플레이어가 가진 아이템, 36개까지만 가능
	std::vector<tagItemInfo>::iterator itemI;

	int curFundsInt = 0;
	int totalEarningsInt = 0;

	GameObject* AddUi(GameObject* go);
	GameObject* AddUi2(UiType t, GameObject* go);
	bool Exist(GameObject* go);
	bool Exist2(GameObject* go);


	std::list<GameObject*> uiObjects;
	std::multimap<UiType, GameObject*> multiMap; // 멀티맵으로 ui오브젝트 탐색

	Player2* player;
	UiButton bag;
	UiButton map;
	UiButton make;
	UiButton changeScene;
	UiButton xButton;
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

	void addItem(tagItemInfo item);

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
};