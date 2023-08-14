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
}

void Slot::Draw(sf::RenderWindow& window)
{
	UiButton::Draw(window);
}
