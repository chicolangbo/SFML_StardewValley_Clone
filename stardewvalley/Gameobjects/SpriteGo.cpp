#include "stdafx.h"
#include "SpriteGo.h"
#include "Utils.h"
#include "ResourceMgr.h"
// �����, 230809, �ݶ��̴� ����
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
	// �����, 230809, �ݶ��̴� ����
	collider.setPosition(p);
	//
}

void SpriteGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	sprite.setPosition(position);
	// �����, 230809, �ݶ��̴� ����
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
	// �����, 230809, �ݶ��̴� ����
	Utils::SetOrigin(collider, origin);
	//
}

void SpriteGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	sprite.setOrigin(x, y);
	// �����, 230809, �ݶ��̴� ����
	collider.setOrigin(x,y);
	//

}

void SpriteGo::SetScale(float x, float y)
{
	sprite.setScale(x, y);
	// �����, 230809, �ݶ��̴� ����
	collider.setScale(x, y);
	//
}

void SpriteGo::SetScale(const sf::Vector2f& p)
{
	sprite.setScale(p);
	// �����, 230809, �ݶ��̴� ����
	collider.setScale(p);
	//
}

void SpriteGo::NineSlice()
{
	sf::Sprite tempSprite;
	float width = sprite.getGlobalBounds().width;
	float height = sprite.getGlobalBounds().height;
	sf::IntRect corner0 = { 0.f, 0.f, width / 3.f, height / 3.f };
	sf::IntRect corner1 = { width - (width / 3.f), 0.f, width/3.f, height / 3.f };
	sf::IntRect corner2 = { 0.f, height - (height / 3.f), width / 3.f, height / 3.f};
	sf::IntRect corner3 = { width - (width / 3.f), height - (height / 3.f), width / 3.f, height / 3.f};
	sf::IntRect edge0 = { width / 3.f, 0.f, width / 3.f, height / 3.f};
	sf::IntRect edge1 = { width / 3.f * 2.f, height / 3.f, width / 3.f, height / 3.f};
	sf::IntRect edge2 = { width / 3.f, height / 3.f * 2.f, width / 3.f, height / 3.f};
	sf::IntRect edge3 = { 0.f, height / 3.f, width / 3.f, height / 3.f};
	sf::IntRect center = { width / 3.f, height / 3.f, width / 3.f, height / 3.f};

	cornerSprite[0].setTextureRect(corner0);
	cornerSprite[1].setTextureRect(corner1);
	cornerSprite[2].setTextureRect(corner2);
	cornerSprite[3].setTextureRect(corner3);

	edgeSprite[0].setTextureRect(edge0);
	edgeSprite[1].setTextureRect(edge1);
	edgeSprite[2].setTextureRect(edge2);
	edgeSprite[3].setTextureRect(edge3);

	centerSprite.setTextureRect(center);
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

		// �����, 230810, 9slice
		centerSprite.setTexture(*tex);
		for (int i = 0; i < 4; ++i)
		{
			cornerSprite[i].setTexture(*tex);
			edgeSprite[i].setTexture(*tex);
		}
		//
	}

	// �����, 230807, ��������Ʈ��Ʈ �� �����̹��� ��� �����ϰԲ� �߰�
	if (tex != nullptr && &nickName != nullptr)
	{
		// �����, 230808, ������ �Ű����� 1���� ���̷��� ����
		sf::IntRect tempRect = RESOURCE_MGR.GetTextureRect(nickName);
		if (tempRect != sf::IntRect{ 0, 0, 0, 0 })
		{
			sprite.setTextureRect(tempRect);
		}
	}
	//
	// �����, 230809, �ݶ��̴� ����
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
