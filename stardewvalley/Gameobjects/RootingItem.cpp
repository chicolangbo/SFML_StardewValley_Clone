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
	SetPosition(position);
	
}

void RootingItem::Release()
{
	SpriteGo::Release();
}

void RootingItem::Reset()
{
	SpriteGo::Reset();
	sprite.setScale(5.f, 5.f);
	
	//directionX = Utils::RandomRange(-1, 1);
	pongspeed = Utils::RandomRange(-1300, -700);
	randX = Utils::RadomOneOrTwo(-1, 1);
}

void RootingItem::Update(float dt)
{
	SpriteGo::Update(dt);

	//일단 플레이어를 따라감
	pos = GetPosition();
 
	if (pong)
	{
		pongspeed += gravity * dt;
		pos.y += pongspeed * dt;
		if (saveY <= pos.y)
		{
			pos.y = saveY;
			pong = false;
		}
	}

	if (!pong)
	{
		pongend = true;
		direction = Utils::Normalize(player->GetPosition() - GetPosition());
		sprite.setRotation(Utils::Angle(look));
		float distance = Utils::Distance(player->GetPosition(), GetPosition());
		if (distance < 300.f)
		{
			pos += direction * speed * dt;
			SetPosition(pos);
		}
	}
	else
	{
		//pos.x += speed * dt * randX; 
		pos.y += speed * dt;

		SetPosition(pos);
	}

}

void RootingItem::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
