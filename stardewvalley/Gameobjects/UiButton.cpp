#include "stdafx.h"
#include "UiButton.h"
#include "InputMgr.h"
#include "SceneMgr.h"

UiButton::UiButton(const std::string& textureId, const std::string& n, const std::string& nickname)
	:SpriteGo(textureId, n, nickname)
{
}

UiButton::~UiButton()
{
}

void UiButton::Init()
{
	SpriteGo::Init();
	colliderOnOff = false;
}

void UiButton::Release()
{
	SpriteGo::Release();
}

void UiButton::Reset()
{
	SpriteGo::Reset();
	isHover = false;
}

void UiButton::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	text.setPosition(p);
}

void UiButton::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
	text.setPosition(x, y);
}

void UiButton::SetOrigin(Origins origin)
{
	SpriteGo::SetOrigin(origin);
	Utils::SetOrigin(text, origin);
	//text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
}

void UiButton::SetOrigin(float x, float y)
{
	SpriteGo::SetOrigin(x,y);
	text.setOrigin(x, y);
}

void UiButton::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f worldMousePos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

	bool prevHover = isHover;
	bool prevHoverWorld = isHoverWorld;
	isHover = sprite.getGlobalBounds().contains(uiMousePos);
	isHoverWorld = sprite.getGlobalBounds().contains(worldMousePos);

	// ±è¹ÎÁö, 230815, setActive false¸é ¾È ÇÏµµ·Ï ¼öÁ¤
	if (this->GetActive())
	{
		if (!prevHover && isHover)
		{
			if(OnEnter != nullptr)
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
		if (isHover && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			if (OnClick != nullptr)
			{
				OnClick();
			}
		}
		// world
		if (!prevHoverWorld && isHoverWorld)
		{
			if(OnEnterWorld != nullptr)
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

void UiButton::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	// ±è¹ÎÁö, 230813, Ãß°¡
	window.draw(text);
}