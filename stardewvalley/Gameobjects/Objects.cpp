#include "stdafx.h"
#include "Objects.h"

void Objects::Init()
{
	SpriteGo::Init();

	
	sprite.setScale({ 4.5f, 4.5f });
}

void Objects::Reset()
{
	SpriteGo::Reset();

	sprite.setTextureRect(texRect);
	SetOrigin(Origins::TL);

	SetColliderSize(tileSize);
	SetPosition(mapLT.x + tileSize.x * indexX, mapLT.y + tileSize.y * indexY);
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
