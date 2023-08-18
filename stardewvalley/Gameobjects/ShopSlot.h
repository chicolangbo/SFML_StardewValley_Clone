#pragma once
#include "UiButton.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SliceImageGo.h"

class ShopSlot :
    public UiButton
{
protected:
    ItemId id = ItemId::none;
    SpriteGo iconCell;
    SpriteGo itemIcon;
    TextGo itemText;
    SpriteGo coin;
    TextGo coinText;

public:
    SliceImageGo cellBox;
    int shopSlotIndex = 0;

    ShopSlot(ItemId id, const std::string& textureId, const std::string& n, sf::Rect<float> centerRect, sf::Rect<float> size, int vc, const std::string& nickName = "");
    virtual ~ShopSlot() override;

    void SetOrigin(Origins o);
    void SetPosition(float x, float y);

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    void SetItemId(ItemId i) { id = i; }
};

