#include "stdafx.h"
#include "ShopTap.h"
#include "ShopInterior.h"
#include "Wall.h"

ShopInterior::ShopInterior(const std::string& n)
	: GameObject(n),
    shopInside("map/shopInside.png", "shopInside"),
    pierre("graphics/Pierre.png", "pierre", "pierre"),
    shopCounter1("map/shopInside.png", "shopCounter1", "shopCounter1"),
    shopCounter2("map/shopInside.png", "shopCounter2", "shopCounter2"),
    shopObj1("map/townInterior.png", "shopObj1", "shopMid1"),
    shopObj2_1("map/townInterior.png", "shopObj2_1", "shopMid2"),
    shopObj2_2("map/townInterior.png", "shopObj2_2", "shopMid2"),
    shopObj3_1("map/townInterior.png", "shopObj3_1", "shopMid3"),
    shopObj3_2("map/townInterior.png", "shopObj3_2", "shopMid3"),
    shopObj4("map/shopInside.png", "shopObj4", "shopBox"),
    shopWalls("shopWalls")
{
    AddInteriors(&shopInside);
    AddInteriors(&pierre);
    AddInteriors(&shopCounter1);
    AddInteriors(&shopCounter2);
    AddInteriors(&shopObj1);
    AddInteriors(&shopObj2_1);
    AddInteriors(&shopObj2_2);
    AddInteriors(&shopObj3_1);
    AddInteriors(&shopObj3_2);
    AddInteriors(&shopObj4);
    AddInteriors(&shopWalls);
}

ShopInterior::~ShopInterior()
{
	Release();
}

GameObject* ShopInterior::AddInteriors(GameObject* go)
{
    if (!Exist(go))
    {
        shopInteriors.push_back(go);
    }
    return go;
}

bool ShopInterior::Exist(GameObject* go)
{
    for (auto& m : shopInteriors)
    {
        if (m == go)
        {
            return true;
        }
    }
    return false;
}

void ShopInterior::Init()
{
    for (auto i : shopInteriors)
    {
        i->Init();
    }
    //pierre.OnClickWorld = [this]() {
    //    std::cout << "pierre" << std::endl;
    //};
}

void ShopInterior::Reset()
{
    for (auto i : shopInteriors)
    {
        i->Reset();
    }

    // SHOP INTERIOR
    {
        shopInside.SetOrigin(Origins::TL);
        shopInside.SetScale(4.f, 4.f);
        shopInside.SetPosition(0, 0);

        pierre.SetOrigin(Origins::MC);
        pierre.SetScale(5.f, 5.f);
        pierre.SetPosition(244.f, 1086.f);

        shopCounter1.SetOrigin(Origins::TL);
        shopCounter1.SetScale(4.f, 4.f);
        shopCounter1.SetPosition(48.f * 4, 275.f * 4);

        shopCounter2.SetScale(4.f, 4.f);
        shopCounter2.SetOrigin(Origins::TL);
        shopCounter2.SetPosition(128.f * 4, 254.f * 4);

        shopObj1.SetScale(4.f, 4.f);
        shopObj1.SetOrigin(Origins::TL);
        shopObj1.SetPosition(48.f * 4, 332.f * 4);
        shopObj1.collider.setScale(1.f, 0.5f);
        shopObj1.collider.setPosition(shopObj1.GetPosition() + sf::Vector2f(0.f, shopObj1.sprite.getGlobalBounds().height / 2.f));

        shopObj2_1.SetScale(4.f, 4.f);
        shopObj2_1.SetOrigin(Origins::TL);
        shopObj2_1.SetPosition(160.f * 4, 277.f * 4);
        shopObj2_1.collider.setScale(1.f, 0.5f);
        shopObj2_1.collider.setPosition(shopObj2_1.GetPosition() + sf::Vector2f(0.f, shopObj2_1.sprite.getGlobalBounds().height / 2.f));
        shopObj2_2.SetScale(4.f, 4.f);
        shopObj2_2.SetOrigin(Origins::TL);
        shopObj2_2.SetPosition(160.f * 4, 325.f * 4);
        shopObj2_2.collider.setScale(1.f, 0.5f);
        shopObj2_2.collider.setPosition(shopObj2_2.GetPosition() + sf::Vector2f(0.f, shopObj2_2.sprite.getGlobalBounds().height / 2.f));
        shopObj3_1.SetScale(4.f, 4.8f);
        shopObj3_1.SetOrigin(Origins::TL);
        shopObj3_1.SetPosition(160.f * 4, 375.f * 4);
        shopObj3_1.collider.setScale(1.f, 0.5f);
        shopObj3_1.collider.setPosition(shopObj3_1.GetPosition() + sf::Vector2f(0.f, shopObj3_1.sprite.getGlobalBounds().height / 2.f));
        shopObj3_2.SetScale(4.f, 4.8f);
        shopObj3_2.SetOrigin(Origins::TL);
        shopObj3_2.SetPosition(224.f * 4, 375.f * 4);
        shopObj3_2.collider.setScale(1.f, 0.5f);
        shopObj3_2.collider.setPosition(shopObj3_2.GetPosition() + sf::Vector2f(0.f, shopObj3_2.sprite.getGlobalBounds().height / 2.f));
        shopObj4.SetScale(4.f, 4.f);
        shopObj4.SetOrigin(Origins::TL);
        shopObj4.SetPosition(288.f * 4, 434.f * 4);
        shopWalls.SetType(Wall::Location::Shop);
        shopWalls.SetPos();
    }
}

void ShopInterior::Release()
{
    
}

void ShopInterior::Update(float dt)
{
    for (auto i : shopInteriors)
    {
        i->Update(dt);
    }
}

void ShopInterior::Draw(sf::RenderWindow& window)
{
    for (auto i : shopInteriors)
    {
        i->Draw(window);
    }
}
