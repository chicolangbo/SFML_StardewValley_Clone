#include "stdafx.h"
#include "Hoe.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "Scene.h"

void Hoe::Init()
{
	SpriteGo::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Hoe_Back.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Hoe_Front.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Hoe_Side.csv"));

	animation.SetTarget(&sprite);
	sprite.setScale(4.5f, 4.5f);

	SetOrigin(Origins::BC);
}

void Hoe::Reset()
{
	SetOrigin(origin);
	SetPosition({ 0, 0 });
	SetFlipX(false);
}

void Hoe::Update(float dt)
{
	animation.Update(dt);
}

void Hoe::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Hoe::PlayAnimation(sf::String name)
{
	animation.Play(name);
}

void Hoe::SetPostion(sf::Vector2f pos)
{
	SetPosition(pos);
}

void Hoe::SetOrigins()
{
	SetOrigin(Origins::MC);
}

bool Hoe::GetFlipX() const
{
	return flipX;
}

void Hoe::SetFlipX(bool flip)
{
	flipX = flip;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !flipX ? -abs(scale.x) : abs(scale.x);
	sprite.setScale(scale);
}
