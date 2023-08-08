#include "stdafx.h"
#include "SpriteGo.h"
#include "Utils.h"
#include "ResourceMgr.h"

SpriteGo::SpriteGo(const std::string& textureId, const std::string& n, const std::string& nickName)
	: GameObject(n), textureId(textureId), nickName(nickName)
{
}

SpriteGo::~SpriteGo()
{
}

void SpriteGo::SetPosition(const sf::Vector2f& p)
{
	position = p;
	sprite.setPosition(p);
}

void SpriteGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	sprite.setPosition(position);
}

void SpriteGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(sprite, origin);
	}
}

void SpriteGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	sprite.setOrigin(x, y);
}

void SpriteGo::Init()
{

}

void SpriteGo::Release()
{
}

void SpriteGo::Reset()
{
	sf::Texture* tex = RESOURCE_MGR.GetTexture(textureId);

	if (tex != nullptr)
	{
		sprite.setTexture(*tex);
	}

	// 김민지, 230807, 스프라이트시트 속 단일이미지 사용 가능하게끔 추가
	if (tex != nullptr && &nickName != nullptr)
	{
		sf::IntRect tempRect = RESOURCE_MGR.GetTextureRect(nickName);
		sprite.setTextureRect(tempRect);
	}
	//
	SetOrigin(origin);
}

void SpriteGo::Update(float dt)
{
}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
