#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SliceImageGo.h"

class ShopSlot :
    public GameObject
{
protected:
    ItemId id = ItemId::none;
    SpriteGo iconCell;
    SpriteGo itemIcon;
    TextGo itemText;
    SpriteGo coin;
    TextGo coinText;
    bool isHover = false;

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
    ItemId GetItemId() { return id; }

    function<void()> OnClick;
    function<void()> OnEnter;
    function<void()> OnExit;
};

