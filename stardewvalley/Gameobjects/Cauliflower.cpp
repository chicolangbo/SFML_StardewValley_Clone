#include "stdafx.h"
#include "Cauliflower.h"
#include "SceneMgr.h"
#include "Scene.h"

Cauliflower::Cauliflower(const string& textureId, const string& n, const string& nickname)
	:Crop(textureId, n, nickname)
{
}

Cauliflower::~Cauliflower()
{
}

void Cauliflower::Init()
{
	Crop::Init();
	id = CropId::Cauliflower;
}

void Cauliflower::Release()
{
	Crop::Release();
}

void Cauliflower::Reset()
{
	Crop::Reset();
}

void Cauliflower::Update(float dt)
{
	Crop::Update(dt);

	if (animationTime <= time)
	{
		time = 0;
		SCENE_MGR.GetCurrScene()->RemoveGo(this);
		pool->Return(this);
	}
}
