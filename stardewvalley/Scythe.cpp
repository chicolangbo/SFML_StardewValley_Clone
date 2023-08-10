#include "stdafx.h"
#include "Scythe.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "Scene.h"

void Scythe::Init()
{
	SpriteGo::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Scythe_Front.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Scythe_Side.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Scythe_Back.csv"));

	animation.SetTarget(&sprite);
	sprite.setScale(4.5f, 4.5f);

	SetOrigin(Origins::BC);
}

void Scythe::Reset()
{
	SetOrigin(origin);
	SetPosition({ 0, 0 });
	SetFlipX(false);
}

void Scythe::Update(float dt)
{
	animation.Update(dt);
}

void Scythe::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Scythe::PlayAnimation(sf::String name)
{
	animation.Play(name);
}

void Scythe::SetPostion(sf::Vector2f pos)
{
	SetPosition(pos);
}

void Scythe::SetOrigins()
{
	SetOrigin(Origins::MC);
}

bool Scythe::GetFlipX() const
{
	return flipX;
}

void Scythe::SetFlipX(bool flip)
{
	flipX = flip;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !flipX ? -abs(scale.x) : abs(scale.x);
	sprite.setScale(scale);
}
