#include "stdafx.h"
#include "RectButton.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"

RectButton::RectButton(const string& path, sf::Vector2f size, const string& n)
	:RectangleGo(size, n)
{
	text.setFont(*RESOURCE_MGR.GetFont(path));
}

RectButton::~RectButton()
{
}

void RectButton::Init()
{
	RectangleGo::Init();
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::Transparent);
}

void RectButton::Release()
{
	RectangleGo::Release();
}

void RectButton::Reset()
{
	RectangleGo::Reset();
	isHover = false;
}

void RectButton::SetPosition(const sf::Vector2f p)
{
	RectangleGo::SetPosition(p);
	text.setPosition(p);
}

void RectButton::SetPosition(float x, float y)
{
	RectangleGo::SetPosition(x,y);
	text.setPosition(x,y);
}

void RectButton::SetOrigin(Origins origin)
{
	RectangleGo::SetOrigin(origin);
	Utils::SetOrigin(text, origin);
}

void RectButton::SetOrigin(float x, float y)
{
	RectangleGo::SetPosition(x, y);
	text.setPosition(x, y);
}

void RectButton::Update(float dt)
{
	RectangleGo::Update(dt);

	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f worldMousePos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

	bool prevHover = isHover;
	bool prevHoverWorld = isHoverWorld;
	isHover = rectangle.getGlobalBounds().contains(uiMousePos);
	isHoverWorld = rectangle.getGlobalBounds().contains(worldMousePos);

	// ±è¹ÎÁö, 230815, setActive false¸é ¾È ÇÏµµ·Ï ¼öÁ¤
	if (this->GetActive())
	{
		if (!prevHover && isHover)
		{
			if (OnEnter != nullptr)
			{
				OnEnter();
			}
		}
		if (prevHover && !isHover)
		{
			if (OnExit != nullptr)
			{
				OnExit();
			}
		}
		if (isHover && INPUT_MGR.GetMouseButtonUp(sf::Mouse::Left))
		{
			if (OnClick != nullptr)
			{
				OnClick();
			}
		}
		// world
		if (!prevHoverWorld && isHoverWorld)
		{
			if (OnEnterWorld != nullptr)
			{
				OnEnterWorld();
			}
		}
		if (prevHoverWorld && !isHoverWorld)
		{
			if (OnExitWorld != nullptr)
			{
				OnExitWorld();
			}
		}
		if (isHoverWorld && INPUT_MGR.GetMouseButtonUp(sf::Mouse::Left))
		{
			if (OnClickWorld != nullptr)
			{
				OnClickWorld();
			}
		}
	}

}

void RectButton::Draw(sf::RenderWindow& window)
{
	RectangleGo::Draw(window);
	window.draw(text);
}
