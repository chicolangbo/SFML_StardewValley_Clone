#include "stdafx.h"
#include "Stone.h"
#include "ResourceMgr.h"

void Stone::Init()
{
	Objects::Init();
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Stone.csv"));

	animation.SetTarget(&sprite);
	//sprite.setScale(0.5f, 0.5f);
	SetOrigin(Origins::TL);

}

void Stone::Reset()
{
	Objects::Reset();

	SetPosition(position);
}

void Stone::Update(float dt)
{
	Objects::Update(dt);
	if (bang)
	{
		SetPosition(position.x +20.f, position.y +70.f);
		SetOrigin(Origins::BC);
		animation.Play("Stone");
		bang = false;
	}
	animation.Update(dt);

}
