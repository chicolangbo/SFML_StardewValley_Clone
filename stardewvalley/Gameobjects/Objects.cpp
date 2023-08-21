#include "stdafx.h"
#include "Objects.h"

void Objects::Init()
{
	SpriteGo::Init();

	SetOrigin(Origins::TL);
	sprite.setScale({ 4.5f, 4.5f });
}

void Objects::Reset()
{
	SpriteGo::Reset();

	SetPosition(mapLT.x + tileSize.x * indexX, mapLT.y + tileSize.y * indexY);
	sprite.setTextureRect(texRect);
	SetColliderSize(tileSize);
}

void Objects::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Objects::SetType(int x, int y, sf::IntRect tex, sf::Vector2f size)
{
	indexX = x;
	indexY = y;
	texRect = tex;
	tileSize = size;
}

void Objects::SetMapLT(sf::Vector2f pos)
{
	mapLT = pos;
}
