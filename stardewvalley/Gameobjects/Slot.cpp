#include "stdafx.h"
#include "Slot.h"

Slot::Slot(const std::string& textureId, const std::string& n, const std::string& nickName)
	: UiButton(textureId, n, nickName)
{
}

Slot::~Slot()
{
}

void Slot::Init()
{
	UiButton::Init();
	OnClick = [this]() {
		//1. 현재 마우스에 붙어있는 게 없고, 아이템이 들어있는 경우
		if (!isEmpty && mouseIcon->IsItemIconEmpty())
		{
			// 마우스에 아이콘이 따라다니도록 한다.
			mouseIcon->SetItemIcon(itemIcon);
			mouseIcon->SetItemId(id);
			id = ItemId::none;
			itemIcon = nullptr;
			isEmpty = true;
			return;
		}

		//2. 현재 마우스에 붙어있는 게 있고, 아이템이 없는 경우
		if (isEmpty && !mouseIcon->IsItemIconEmpty())
		{
			// 마우스에 달린 아이콘이 해당 셀에 정착된다.
			id = mouseIcon->GetItemId();
			itemIcon = mouseIcon->GetItemIcon();
			mouseIcon->SetItemIcon(nullptr);
			mouseIcon->SetItemId(ItemId::none);
			isEmpty = false;
			return;
		}

		// 3. 현재 마우스에 붙어있는 게 있고, 아이템이 들어있는 경우
		if (!isEmpty && !mouseIcon->IsItemIconEmpty())
		{
			// 마우스에 달린 아이콘은 해당 셀에 정착, 셀에 있던 아이콘이 마우스에 정착
			SpriteGo* tempIcon = mouseIcon->GetItemIcon();
			ItemId tempId = mouseIcon->GetItemId();
			mouseIcon->SetItemIcon(itemIcon);
			mouseIcon->SetItemId(id);
			SetItemIcon(tempIcon);
			id = tempId;
			isEmpty = false;
			return;
		}
	};
	OnEnter = [this]() {

	};
	OnExit = [this]() {

	};
}

void Slot::Release()
{
	UiButton::Release();
}

void Slot::Reset()
{
	UiButton::Reset();
}

void Slot::Update(float dt)
{
	UiButton::Update(dt);
	UpdateIsEmpty();
}

void Slot::Draw(sf::RenderWindow& window)
{
	UiButton::Draw(window);
	if (itemIcon != nullptr)
	{
		itemIcon->SetPosition(position);
		itemIcon->Draw(window);
	}
}

void Slot::UpdateIsEmpty()
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
