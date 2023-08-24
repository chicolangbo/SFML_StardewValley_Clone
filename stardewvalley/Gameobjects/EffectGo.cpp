#include "stdafx.h"
#include "EffectGo.h"
#include "ResourceMgr.h"


EffectGo::EffectGo(const std::string& textureId, const std::string& n)
	:SpriteGo("", "")
{
	animationName = textureId;
	name = n;
}

void EffectGo::Init()
{
	SpriteGo::Init(); 

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip(animationName)); 
	animation.SetTarget(&sprite);
	sprite.setScale(1.5f, 1.5f); 
	SetOrigin(Origins::BC);
}

void EffectGo::Reset()
{
	SpriteGo::Reset(); 
	animation.Play(name); 
}

void EffectGo::Update(float dt)
{
	SpriteGo::Update(dt); 
	animation.Update(dt); 
}

void EffectGo::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window); 
}
