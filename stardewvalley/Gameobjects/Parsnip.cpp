#include "stdafx.h"
#include "Parsnip.h"
#include "SceneMgr.h"
#include "Scene.h"

Parsnip::Parsnip(const string& textureId, const string& n, const string& nickname)
	:Crop(textureId, n, nickname)
{
}

Parsnip::~Parsnip()
{
}

void Parsnip::Init()
{
	Crop::Init();
	id = CropId::Parsnip;
}

void Parsnip::Release()
{
	Crop::Release();
}

void Parsnip::Reset()
{
	Crop::Reset();
}

void Parsnip::Update(float dt)
{
	Crop::Update(dt);

	if (animationTime <= time)
	{
		time = 0;
		SCENE_MGR.GetCurrScene()->RemoveGo(this);
		pool->Return(this);
	}
}
