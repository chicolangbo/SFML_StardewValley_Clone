#include "stdafx.h"
#include "Timber.h"
#include "ResourceMgr.h"

void Timber::Init()
{
	Objects::Init();
	


}

void Timber::Reset()
{
	Objects::Reset();

	SetPosition(position);

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Timber.csv"));
	animation.SetTarget(&sprite);

	SetOrigin(Origins::TL);
}

void Timber::Update(float dt)
{
	Objects::Update(dt);
	if (bang)
	{
		SetScale(1.5f, 1.5f);
		SetPosition(position.x,position.y);
		SetOrigin(Origins::BC);
		animation.Play("Timber");
		bang = false;
	}


	animation.Update(dt);
}
