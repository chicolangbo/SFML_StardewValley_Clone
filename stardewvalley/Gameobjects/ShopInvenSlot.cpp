#include "stdafx.h"
#include "ShopInvenSlot.h"
#include "DataTableMgr.h"
#include "AllItemTable.h"

ShopInvenSlot::ShopInvenSlot(const std::string& textureId, const std::string& n, const std::string& nickName)
	: UiButton(textureId, n, nickName),
	count("count", "fonts/Galmuri7.ttf")
{
}

ShopInvenSlot::~ShopInvenSlot()
{
}

void ShopInvenSlot::Init()
{
	UiButton::Init();
}

void ShopInvenSlot::Release()
{
	UiButton::Release();
}

void ShopInvenSlot::Reset()
{
	UiButton::Reset();
	count.Reset();
	count.SetString("0");
	count.SetOrigin(Origins::BR);
	count.text.setCharacterSize(15);
	count.text.setFillColor(sf::Color::White);
	count.text.setOutlineThickness(2);
	count.text.setOutlineColor(sf::Color::Black);
}

void ShopInvenSlot::Update(float dt)
{
	UiButton::Update(dt);
	UpdateIsEmpty();
}

void ShopInvenSlot::Draw(sf::RenderWindow& window)
{
	UiButton::Draw(window);
	if (id == ItemId::craftScareCrow)
	{
		itemIcon->SetScale(2.2f, 2.2f);
		itemIcon->sprite.setRotation(30.f);
	}

	if (itemIcon != nullptr)
	{
		itemIcon->SetPosition(position);
		itemIcon->Draw(window);
		count.Draw(window);
	}
}

void ShopInvenSlot::UpdateIsEmpty()
{
	if (IsItemIconEmpty())
	{
		isEmpty = true;
		id = ItemId::none;
	}
	else
	{
		isEmpty = false;
	}
}
