#include "stdafx.h"
#include "Axe.h"
#include "Player2.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "Scene.h"


void Axe::Init()
{
	SpriteGo::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Axe_Back.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Axe_Front.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Axe_Side.csv"));
	

	animation.SetTarget(&sprite);
	sprite.setScale(4.5f, 4.5f);

	SetOrigin(Origins::BC);

	
}

void Axe::Reset()
{
	//SpriteGo::Reset();

	SetOrigin(origin); 
	SetPosition({ 0, 0 });
	SetFlipX(false);
}

void Axe::Update(float dt)
{
	//SpriteGo::Update(dt); 
	
	animation.Update(dt);
}

void Axe::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window); 
}

void Axe::PlayAnimation(sf::String name)
{
	animation.Play(name);
}

void Axe::SetPostion(sf::Vector2f pos)
{
	SetPosition(pos);
}

void Axe::SetOrigins()
{
	SetOrigin(Origins::BC);  
}

bool Axe::GetFlipX() const
{
	return flipX;
}

void Axe::SetFlipX(bool flip)
{
	flipX = flip;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !flipX ? -abs(scale.x) : abs(scale.x);  
	sprite.setScale(scale);
}
