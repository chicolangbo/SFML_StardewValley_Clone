#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "SliceImageGo.h"
#include "UiButton.h"
#include "TextGo.h"
#include "Player2.h"
#include "Inventory.h"

class ShopSlot;

class ShopTap :
    public GameObject
{
protected:
    Player2* player;
    Inventory* inven;
    std::list<tagItemInfo>* playerItemList = nullptr;

    // SHOP SLOT VECTOR
    std::vector<ShopSlot*> shopSlot;
    int shopSlotCount = 13;

    // SHOPTAP UI
    std::list<GameObject*> shopUiObjects;
    SpriteGo pierrePortrait;
    TextGo pierreText;
    SliceImageGo pierreTextBox;
    SliceImageGo shopBox;
    SpriteGo moneyBar;
    TextGo moneyText;
    int* moneyInt = nullptr;
    UiButton xButton;
    SliceImageGo invenBox;

public:
    ShopTap(const std::string& n = "");
    virtual ~ShopTap() override;

    GameObject* AddUi(GameObject* go);
    bool Exist(GameObject* go);

    virtual void Init() override;
    virtual void Reset() override;
    virtual void Release() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    void SortGos();
    void SetPlayer(Player2* p) { player = p; }
    void SetInventory(Inventory* i) { this->inven = i; }
    void SetPlayerInfo();
    void PlayerInfoUpdate();
};
