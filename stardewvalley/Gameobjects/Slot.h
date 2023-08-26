#pragma once
#include "UiButton.h"
#include "Item.h"
#include "TextGo.h"

class Slot : public UiButton
{
protected:
    Slot* mouseIcon = nullptr;
    ItemId id = ItemId::none;
    SpriteGo* itemIcon = nullptr;
    bool isEmpty = true;
    TextGo count;
    int countValue = 0;

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
    void SetCountPos(sf::Vector2f p) { count.SetPosition(p); }
    void SetCountString(int c) { count.SetString(to_string(c)); countValue = c; }
    int GetCountValue() { return countValue; }
};

