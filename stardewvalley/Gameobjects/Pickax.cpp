#include "stdafx.h"
#include "Pickax.h"
#include "Player2.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "Scene.h"
#include "RectangleGo.h"


void Pickax::Init()
{
	SpriteGo::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pickax_Front.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pickax_Back.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pickax_Side.csv"));

	animation.SetTarget(&sprite);
	sprite.setScale(4.5f, 4.5f);

	SetOrigin(Origins::BC);

	hitBox.setSize({20.f, 20.f});
	hitBox.setFillColor(sf::Color::Green);
	
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
	SetOrigin(Origins::BC);
}

bool Pickax::GetFlipX() const
{
	return flipX;
}

void Pickax::SetFlipX(bool flip)
{
	flipX = flip;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !flipX ? -abs(scale.x) : abs(scale.x);
	sprite.setScale(scale);
}
