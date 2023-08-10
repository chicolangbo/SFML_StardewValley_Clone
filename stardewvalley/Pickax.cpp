#include "stdafx.h"
#include "Pickax.h"
#include "Player2.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "Scene.h"

void Pickax::Init()
{
	SpriteGo::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pickax_Front.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pickax_Back.csv"));

	animation.SetTarget(&sprite);
	sprite.setScale(5.f, 5.f);

	SetOrigin(Origins::BC);
}

void Pickax::Reset()
{
	SetOrigin(origin);
	SetPosition({ 0, 0 });
}

void Pickax::Update(float dt)
{
	animation.Update(dt);
}

void Pickax::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Pickax::PlayAnimation(sf::String name)
{
	animation.Play(name);
}

void Pickax::SetPostion(sf::Vector2f pos)
{
	SetPosition(pos);
}

void Pickax::SetOrigins()
{
	SetOrigin(Origins::MC);
}
