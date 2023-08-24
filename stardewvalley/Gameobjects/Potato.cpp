#include "stdafx.h"
#include "Potato.h"

Potato::Potato(const string& textureId, const string& n, const string& nickname)
	:Crop(textureId, n, nickname)
{
}

Potato::~Potato()
{
}

void Potato::Init()
{
	Crop::Init();
	id = CropId::Potato;
}

void Potato::Release()
{
	Crop::Release();
}

void Potato::Reset()
{
	Crop::Reset();
}


void Potato::Update(float dt)
{
	Crop::Update(dt);
}
