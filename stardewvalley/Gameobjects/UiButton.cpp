#include "stdafx.h"
#include "UiButton.h"
#include "InputMgr.h"
#include "SceneMgr.h"

UiButton::UiButton(const std::string& textureId, const std::string& n, const std::string& nickName)
	:SpriteGo(textureId, n, nickName)
{
}

UiButton::~UiButton()
{
}

void UiButton::Init()
{
	SpriteGo::Init();
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

void UiButton::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

	bool prevHover = isHover;
	isHover = sprite.getGlobalBounds().contains(uiMousePos);

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
	if (isHover && INPUT_MGR.GetMouseButtonUp(sf::Mouse::Left))
	{
		if (OnClick != nullptr)
		{
			OnClick();
		}
	}

}

void UiButton::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void UiButton::Click()
{
	if (isHover && INPUT_MGR.GetMouseButtonUp(sf::Mouse::Left))
	{
		if (OnClick != nullptr)
		{

			//if마우스에 아무것도 안붙어있으면
			//클릭 됐을 때 아이템객체가 마우스에 달라붙음

			//else이미 붙어있으면
			//마우스 클릭한곳이 인벤토리면 인벤토리로 들어감
		}
	}
}
