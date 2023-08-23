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
	
}

void RootingItem::Update(float dt)
{
	SpriteGo::Update(dt);

	//std::cout << player->GetDirection().y << std::endl;
	//일단 플레이어를 따라감
	pos = GetPosition();
 
	direction = { Utils::RandomRange(-1.f, 1.f),-1.f };
	//pos += direction * dt * speed;

	if (1)
	{
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
		//SetPosition(pos);
	}

}

void RootingItem::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
