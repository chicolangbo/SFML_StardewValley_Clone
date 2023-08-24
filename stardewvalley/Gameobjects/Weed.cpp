#include "stdafx.h"
#include "Weed.h"
#include "ResourceMgr.h"

void Weed::Init()
{
	Objects::Init();
	

}

void Weed::Reset()
{
	Objects::Reset();

	SetPosition(position);

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Weed.csv"));
	animation.SetTarget(&sprite);
	SetOrigin(Origins::TL);
}

void Weed::Update(float dt)
{
	
	Objects::Update(dt);
	if (bang)
	{
		SetScale(1.5f, 1.5f);
		SetPosition(position);
		SetOrigin(Origins::BC);
		animation.Play("Weed");
		bang = false;
	}
	animation.Update(dt);
}
