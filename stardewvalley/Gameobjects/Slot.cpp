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
		//1. ���� ���콺�� �پ��ִ� �� ����, �������� ����ִ� ���
		if (!isEmpty && mouseIcon->IsItemIconEmpty())
		{
			// ���콺�� �������� ����ٴϵ��� �Ѵ�.
			mouseIcon->SetItemIcon(itemIcon);
			mouseIcon->SetItemId(id);
			id = ItemId::none;
			itemIcon = nullptr;
			isEmpty = true;
			return;
		}

		//2. ���� ���콺�� �پ��ִ� �� �ְ�, �������� ���� ���
		if (isEmpty && !mouseIcon->IsItemIconEmpty())
		{
			// ���콺�� �޸� �������� �ش� ���� �����ȴ�.
			id = mouseIcon->GetItemId();
			itemIcon = mouseIcon->GetItemIcon();
			mouseIcon->SetItemIcon(nullptr);
			mouseIcon->SetItemId(ItemId::none);
			isEmpty = false;
			return;
		}

		// 3. ���� ���콺�� �پ��ִ� �� �ְ�, �������� ����ִ� ���
		if (!isEmpty && !mouseIcon->IsItemIconEmpty())
		{
			// ���콺�� �޸� �������� �ش� ���� ����, ���� �ִ� �������� ���콺�� ����
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