#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "Wall.h"

#include "GameObject.h"
class HomeInterior :
    public GameObject
{
protected:
    std::list<GameObject*> homeInteriors;
    SpriteGo homeInside;
    
    Wall homeWalls;

public:
    HomeInterior(const std::string& n = "");
    virtual ~HomeInterior() override;

    GameObject* AddInteriors(GameObject* go);
    bool Exist(GameObject* go);

    virtual void Init() override;
    virtual void Reset() override;
    virtual void Release() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;
};

