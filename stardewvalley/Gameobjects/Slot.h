#pragma once
#include "UiButton.h"
#include "Item.h"

class Slot :
    public UiButton
{
protected:
    SpriteGo* itemIcon = nullptr;
    Slot* mouseIcon = nullptr;
    ItemId id = ItemId::none;

    bool isEmpty = true;

public:
    int slotIndex = 0;
    Slot(const std::string& textureId = "", const std::string& n = "", const std::string& nickName = "");
    virtual ~Slot() override;

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    bool IsItemIconEmpty() { return itemIcon == nullptr; }
    void SetItemIcon(SpriteGo* i) { itemIcon = i; }
    SpriteGo* GetItemIcon() { return itemIcon; }
    void SetMouseIcon(Slot* m) { mouseIcon = m; }
    void UpdateIsEmpty();
    void SetItemId(ItemId i) { id = i; }
    ItemId GetItemId() { return id; }
};
