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
	sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

	bool prevHover = isHover;
	isHover = sprite.getGlobalBounds().contains(uiMousePos);

	// 김민지, 230815, setActive false면 안 하도록 수정
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
		if (isHover && INPUT_MGR.GetMouseButtonUp(sf::Mouse::Left))
		{
			if (OnClick != nullptr)
			{
				OnClick();
			}
		}
	}
}

void UiButton::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	// 김민지, 230813, 추가
	window.draw(text);
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
