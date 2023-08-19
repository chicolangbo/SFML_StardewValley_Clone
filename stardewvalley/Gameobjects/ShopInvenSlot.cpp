#include "stdafx.h"
#include "ShopInvenSlot.h"
#include "DataTableMgr.h"
#include "AllItemTable.h"

ShopInvenSlot::ShopInvenSlot(const std::string& textureId, const std::string& n, const std::string& nickName)
	: UiButton(textureId, n, nickName)
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
}

void ShopInvenSlot::Update(float dt)
{
	UiButton::Update(dt);
	UpdateIsEmpty();
}

void ShopInvenSlot::Draw(sf::RenderWindow& window)
{
	UiButton::Draw(window);
	if (itemIcon != nullptr)
	{
		itemIcon->SetPosition(position);
		itemIcon->Draw(window);
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
