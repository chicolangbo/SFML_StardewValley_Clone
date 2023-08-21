#pragma once
#include "UiButton.h"
#include "Item.h"

class ShopInvenSlot :
    public UiButton
{
protected:
    ItemId id = ItemId::none;
    SpriteGo* itemIcon = nullptr;
    bool isEmpty = true;

public:
    int slotIndex = 0;
    ShopInvenSlot(const std::string& textureId = "", const std::string& n = "", const std::string& nickName = "");
    virtual ~ShopInvenSlot() override;

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;
  

    bool IsItemIconEmpty() { return itemIcon == nullptr; }
    void SetItemIcon(SpriteGo* i) { itemIcon = i; }
    SpriteGo* GetItemIcon() { return itemIcon; }
    void UpdateIsEmpty();
    void SetItemId(ItemId i) { id = i; }
    ItemId GetItemId() { return id; }
};

