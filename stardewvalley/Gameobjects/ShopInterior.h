#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "Wall.h"
#include "UiButton.h"

class ShopInterior :
    public GameObject
{
protected:
    // SHOP INERIOR UI
    std::list<GameObject*> shopInteriors;
    std::list<SpriteGo> shopInteriosSp;

    SpriteGo shopInside;
    UiButton pierre;
    SpriteGo shopCounter1;
    SpriteGo shopCounter2;
    SpriteGo shopObj1;
    SpriteGo shopObj2_1;
    SpriteGo shopObj2_2;
    SpriteGo shopObj3_1;
    SpriteGo shopObj3_2;
    SpriteGo shopObj4;
    Wall shopWalls;

public:
    ShopInterior(const std::string& n = "");
    virtual ~ShopInterior() override;

    GameObject* AddInteriors(GameObject* go);
    bool Exist(GameObject* go);
    std::list<SpriteGo> GetshopInteriors() { return shopInteriosSp; }
    Wall GetWall() { return shopWalls; }

    virtual void Init() override;
    virtual void Reset() override;
    virtual void Release() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    UiButton* GetPierre() { return &pierre; }
};

