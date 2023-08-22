#include "stdafx.h"
#include "HomeInterior.h"

HomeInterior::HomeInterior(const std::string& n)
    : GameObject(n),
    homeInside("map/FarmhouseInside.png", "homeInside"),
    homeWalls("homeWalls")
{
    AddInteriors(&homeInside);
    AddInteriors(&homeWalls);
}

HomeInterior::~HomeInterior()
{
    Release();
}

GameObject* HomeInterior::AddInteriors(GameObject* go)
{
    if (!Exist(go))
    {
        homeInteriors.push_back(go);
    }
    return go;
}

bool HomeInterior::Exist(GameObject* go)
{
    for (auto& m : homeInteriors)
    {
        if (m == go)
        {
            return true;
        }
    }
    return false;
}

void HomeInterior::Init()
{
    for (auto i : homeInteriors)
    {
        i->Init();
    }
}

void HomeInterior::Reset()
{
    for (auto i : homeInteriors)
    {
        i->Reset();
    }

    homeInside.SetOrigin(Origins::TL);
    homeInside.SetPosition(0, 0);

    homeWalls.SetType(Location::Home);
    homeWalls.SetPos();
}

void HomeInterior::Release()
{
}

void HomeInterior::Update(float dt)
{
    for (auto i : homeInteriors)
    {
        i->Update(dt);
    }
}

void HomeInterior::Draw(sf::RenderWindow& window)
{
    for (auto i : homeInteriors)
    {
        i->Draw(window);
    }
}