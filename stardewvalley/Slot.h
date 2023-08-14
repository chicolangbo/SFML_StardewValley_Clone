#pragma once
#include "UiButton.h"
#include "Item.h"

class Slot :
    public UiButton
{
protected:
    sf::Sprite slotBg;
    SpriteGo itemIcon;
    std::vector<tagItemInfo>* playerItemList = nullptr;

    bool isEmpty;
    int slotIndex;

public:
    Slot(const std::string& textureId, const std::string& n, const std::string& nickName = "");
    ~Slot();

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;
    void SetPlayerItemList(std::vector<tagItemInfo>* itemList) { playerItemList = itemList; }
};

