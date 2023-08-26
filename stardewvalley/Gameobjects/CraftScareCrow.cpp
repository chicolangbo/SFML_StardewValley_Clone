#include "stdafx.h"
#include "CraftScareCrow.h"

CraftScareCrow::CraftScareCrow(const std::string& textureId, const std::string& n, const std::string& nickName)
	: CraftGo(textureId, n, nickName)
{
}

CraftScareCrow::~CraftScareCrow()
{
}

void CraftScareCrow::Init()
{
	CraftGo::Init();
}

void CraftScareCrow::Release()
{
	CraftGo::Release();
}

void CraftScareCrow::Reset()
{
	scareCrawIngredients.push_back(std::make_pair(ItemId::branch, 50));
	scareCrawIngredients.push_back(std::make_pair(ItemId::coal, 1));
	scareCrawIngredients.push_back(std::make_pair(ItemId::fiver, 20));
	ingredients = &scareCrawIngredients;
	ingredientsCount = scareCrawIngredients.size();

	CraftGo::Reset();
}

void CraftScareCrow::Update(float dt)
{
	CraftGo::Update(dt);
}
