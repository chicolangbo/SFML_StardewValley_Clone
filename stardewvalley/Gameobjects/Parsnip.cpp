#include "stdafx.h"
#include "Parsnip.h"

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
}
