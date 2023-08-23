#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "SliceImageGo.h"
#include "UiButton.h"
#include "TextGo.h"
#include "Player2.h"
#include "Inventory.h"
#include "RectangleGo.h"

class ShopSlot;
class ShopInvenSlot;

class ShopTap :
    public GameObject
{
protected:
    Player2* player = nullptr;
    UiButton* pierre = nullptr;
    Inventory* inven = nullptr;
    std::list<tagItemInfo>* playerItemList = nullptr;
    std::unordered_map<ItemId, SpriteGo>* itemIconList = nullptr;

    // SHOP, INVEN SLOT VECTOR
    std::vector<ShopSlot*> shopSlot;
    std::vector<ShopInvenSlot*> shopInvenSlot;
    int shopSlotCount = 13;

    // SHOPTAP UI
    std::list<GameObject*> shopUiObjects;
    SpriteGo pierrePortrait;
    TextGo pierreText1;
    TextGo pierreText2;
    TextGo pierreText3;
    TextGo pierreText4;
    SliceImageGo pierreTextBox;
    SliceImageGo shopBox;
    SpriteGo moneyBar;
    TextGo moneyText;
    int* moneyInt = nullptr;
    int* tempMoney = nullptr;
    UiButton xButton;
    SliceImageGo invenBox;
    UiButton scrollUp;
    UiButton scrollDown;

public:
    bool shopTapOn = false;
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
    void SetPierre(UiButton* p) { pierre = p; }

    void InitInfo();

    void ButtonSetUp();
    void PlayerInfoUpdate();
    void IconUpdate();
    void ItemIndexUpdate();

    void TapOnOff();
};

