#include "stdafx.h"
#include "RootingItem.h"

RootingItem::RootingItem(ItemId id, const std::string& textureId, const std::string& n, const std::string& nickName)
	: id(id),SpriteGo(textureId, n, nickName)
{
}

RootingItem::~RootingItem()
{
}

void RootingItem::Init()
{
	SpriteGo::Init();
}

void RootingItem::Release()
{
	SpriteGo::Release();
}

void RootingItem::Reset()
{
	SpriteGo::Reset();
	sprite.setScale(5.f, 5.f);
}

void RootingItem::Update(float dt)
{
	SpriteGo::Update(dt);
}

void RootingItem::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
