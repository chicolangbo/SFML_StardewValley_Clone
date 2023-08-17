#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "SliceImageGo.h"
#include "UiButton.h"
#include "TextGo.h"
#include "Player2.h"
#include "Inventory.h"

class ShopSlot;

class Shop :
    public GameObject
{
protected:
    Player2* player;
    Inventory* inven;
    std::list<tagItemInfo>* playerItemList;

    // SHOP SLOT VECTOR
    std::vector<ShopSlot*> shopSlot;
    int shopSlotCount = 13;

    // UI
    std::list<GameObject*> shopUiObjects;
    SpriteGo pierre;
    TextGo pierreText;
    SliceImageGo pierreTextBox;
    SliceImageGo shopBox;
    SpriteGo moneyBar;
    TextGo moneyText;
    int* moneyInt = nullptr;
    UiButton xButton;
    SliceImageGo invenBox;

public:
    Shop(const std::string& n = "");
    virtual ~Shop() override;

    GameObject* AddUi(GameObject* go);
    bool Exist(GameObject* go);

    virtual void Init() override;
    virtual void Reset() override;
    virtual void Release() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    void SortGos();
    void SetPlayerItemList() { playerItemList = player->GetPlayerItemList(); }
    void SetInventory(Inventory* i) { this->inven = i; }
    void PlayerInfoUpdate();
};

