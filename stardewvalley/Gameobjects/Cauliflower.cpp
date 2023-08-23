#include "stdafx.h"
#include "Cauliflower.h"

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
}
