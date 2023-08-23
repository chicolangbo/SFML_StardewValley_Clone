#include "stdafx.h"
#include "Crop.h"

Crop::Crop(const string& textureId, const string& n, const string& nickname)
	:SpriteGo(textureId, n, nickname)
{
}

Crop::~Crop()
{
}

void Crop::Init()
{
	SpriteGo::Init();
}

void Crop::Release()
{
	SpriteGo::Release();
}

void Crop::Reset()
{
	SpriteGo::Reset();
}

void Crop::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Crop::SetIndex(int x, int y)
{
	index = sf::Vector2i(x, y);
}
