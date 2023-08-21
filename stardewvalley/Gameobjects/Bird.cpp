#include "stdafx.h"
#include "Bird.h"
#include "ResourceMgr.h"

void Bird::Init()
{
	SpriteGo::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/obj.csv"));

	animation.SetTarget(&sprite);
	sprite.setScale(1.5f, 1.5f);
	SetOrigin(Origins::MC);

}

void Bird::Reset()
{
	SpriteGo::Reset();
	animation.Play("Fly");
	//SetPosition({ 0,0 });
}

void Bird::Update(float dt)
{
	SpriteGo::Update(dt);
	animation.Update(dt);
}

void Bird::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
