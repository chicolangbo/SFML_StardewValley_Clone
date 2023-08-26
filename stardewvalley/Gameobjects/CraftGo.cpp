#include "stdafx.h"
#include "CraftGo.h"
#include "Player2.h"

CraftGo::CraftGo(const std::string& textureId, const std::string& n, const std::string& nickName)
	: UiButton(textureId, n, nickName)
{
}

CraftGo::~CraftGo()
{
}

void CraftGo::Init()
{
	UiButton::Init();
}

void CraftGo::Release()
{
	UiButton::Release();
}

void CraftGo::Reset()
{
	UiButton::Reset();
	sprite.setColor(sf::Color(255, 255, 255, 130));
}

void CraftGo::Update(float dt)
{
	UiButton::Update(dt);
}

void CraftGo::CheckCraftPossiblity(std::list<tagItemInfo>* playerItemList)
{
    int temp = 0;

    for (auto& i : *ingredients)
    {
        for (auto& item : *playerItemList)
        {
            if (item.itemId == i.first && item.count >= i.second)
            {
                temp++;
                if (temp == ingredientsCount)
                {
                    craftPossibility = true;
                    sprite.setColor(sf::Color(255, 255, 255, 255));
                    return;
                }
                else
                {
                    break;
                }
            }
        }
    }
    sprite.setColor(sf::Color(255, 255, 255, 130));
}

void CraftGo::Craft(Player2* p, ItemId id)
{
    if (craftPossibility)
    {
        for (auto& i : *ingredients)
        {
            for (int j = 0; j < i.second; ++j)
            {
                p->RemovePlayerItem(i.first);
            }
        }
        p->AddPlayerItem(id);
        CheckCraftPossiblity(p->GetPlayerItemList());
    }
}
