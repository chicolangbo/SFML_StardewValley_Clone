#include "stdafx.h"
#include "Wateringcan.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "Scene.h"


void Wateringcan::Init()
{
    SpriteGo::Init();

    animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Wateringcan_Back.csv"));
    animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Wateringcan_Front.csv"));
    animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Wateringcan_Side.csv"));


    animation.SetTarget(&sprite);
    sprite.setScale(4.5f, 4.5f);

    SetOrigin(Origins::BC);
}

void Wateringcan::Reset()
{
    SetOrigin(origin);
    SetPosition({ 0, 0 });
    SetFlipX(false);
}

void Wateringcan::Update(float dt)
{
    animation.Update(dt);
}

void Wateringcan::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);
}

void Wateringcan::PlayAnimation(sf::String name)
{
    animation.Play(name);
}

void Wateringcan::SetPostion(sf::Vector2f pos)
{
    SetPosition(pos);
}

void Wateringcan::SetOrigins()
{
    SetOrigin(Origins::BC);
}

bool Wateringcan::GetFlipX() const
{
    return flipX;
}

void Wateringcan::SetFlipX(bool flip)
{
    flipX = flip;

    sf::Vector2f scale = sprite.getScale();
    scale.x = !flipX ? -abs(scale.x) : abs(scale.x);
    sprite.setScale(scale);
}
