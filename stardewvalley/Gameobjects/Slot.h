#pragma once
#include "UiButton.h"
#include "Item.h"

class Slot :
    public UiButton
{
protected:
    SpriteGo* itemIcon = nullptr;

    bool isEmpty;
    bool onMouse;

public:
    int slotIndex = 0;
    Slot(const std::string& textureId, const std::string& n, const std::string& nickName = "");
    ~Slot();

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    void SetItemIcon(SpriteGo* i) { itemIcon = i; }
};

