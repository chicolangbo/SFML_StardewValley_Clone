#include "stdafx.h"
#include "SpriteGo.h"
#include "Utils.h"
#include "ResourceMgr.h"
// 김민지, 230809, 콜라이더 연동
#include "InputMgr.h"
//

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
	// 김민지, 230809, 콜라이더 연동
	collider.setPosition(p);
	//
}

void SpriteGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	sprite.setPosition(position);
	// 김민지, 230809, 콜라이더 연동
	collider.setPosition(position);
	//

}

void SpriteGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(sprite, origin);
	}
	// 김민지, 230809, 콜라이더 연동
	Utils::SetOrigin(collider, origin);
	//
}

void SpriteGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	sprite.setOrigin(x, y);
	// 김민지, 230809, 콜라이더 연동
	collider.setOrigin(x,y);
	//

}

void SpriteGo::SetScale(float x, float y)
{
	sprite.setScale(x, y);
	// 김민지, 230809, 콜라이더 연동
	collider.setScale(x, y);
	//
}

void SpriteGo::SetScale(const sf::Vector2f& p)
{
	sprite.setScale(p);
	// 김민지, 230809, 콜라이더 연동
	collider.setScale(p);
	//
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
		// 김민지, 230808, 생성자 매개변수 1개로 줄이려고 수정
		sf::IntRect tempRect = RESOURCE_MGR.GetTextureRect(nickName);
		if (tempRect != sf::IntRect{ 0, 0, 0, 0 })
		{
			sprite.setTextureRect(tempRect);
		}
	}
	//
	// 김민지, 230809, 콜라이더 연동
	collider.setOutlineThickness(2.f);
	collider.setOutlineColor(sf::Color::Red);
	collider.setSize({ sprite.getGlobalBounds().width, sprite.getGlobalBounds().height });
	collider.setFillColor(sf::Color::Transparent);
	//
	SetOrigin(origin);
}

void SpriteGo::Update(float dt)
{
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num0))
	{
		if (colliderOnOff)
		{
			colliderOnOff = false;
		}
		else
		{
			colliderOnOff = true;
		}
	}
}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	if (colliderOnOff)
	{
		window.draw(collider);
	}
}
