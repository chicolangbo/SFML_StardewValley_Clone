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
    Player2* player;
    Inventory* inven;
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
    UiButton xButton;
    SliceImageGo invenBox;
    SliceImageGo scrollBg;
    sf::Vector2f scrollBarSize = {0.f,0.f};
    UiButton scrollBar;
    UiButton scrollUp;
    UiButton scrollDown;

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

    void InitInfo();

    void ButtonSetUp();
    void PlayerInfoUpdate();
    void IconUpdate(); 
};

