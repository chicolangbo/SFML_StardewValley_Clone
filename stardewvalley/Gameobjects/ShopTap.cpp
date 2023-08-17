#include "stdafx.h"
#include "ShopTap.h"
#include "ShopSlot.h"
#include "Wall.h"
#include "Framework.h"
#include "SceneMgr.h"
#include "Framework.h"
#include "StringTable.h"
#include "DataTableMgr.h"

ShopTap::ShopTap(const std::string& n)
	: GameObject(n),
    pierrePortrait("graphics/pierrePortrait.png", "pierrePortrait"),
    pierreText("pierreText", "fonts/SDMiSaeng.ttf"),
    pierreTextBox("graphics/box1.png", "pierreTextBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE),
    shopBox("graphics/box1.png", "pierreTextBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE),
    moneyBar("graphics/Cursors.ko-KR.png", "moneyBar", "money"),
    moneyText("moneyText", "fonts/SDMiSaeng.ttf"),
    xButton("graphics/Cursors.ko-KR.png", "xButton", "xButton"),
    invenBox("graphics/box1.png", "shopInvenBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE)
{
    // SHOP TAP
    AddUi(&pierrePortrait);
    AddUi(&pierreText);
    AddUi(&pierreTextBox);
    AddUi(&shopBox);
    AddUi(&moneyBar);
    AddUi(&moneyText);
    AddUi(&xButton);
    AddUi(&invenBox);
    
    int itemNum = 9;
    for (int i = 0; i < shopSlotCount; ++i)
    {
        std::string num = to_string(i);

        shopSlot.push_back(new ShopSlot((ItemId)itemNum, "graphics/shopCellBox.png", "shopCellBox" + num, { 27,27,26,26 }, {0,0,80,80}, NINE_SLICE));
        shopSlot[i]->shopSlotIndex = i;
        shopSlot[i]->SetOrigin(Origins::MC);
        shopSlot[i]->colliderOnOff = false;
        AddUi(shopSlot[i]);
        itemNum++;
    }
}

ShopTap::~ShopTap()
{
    Release();
}

GameObject* ShopTap::AddUi(GameObject* go)
{
    if (!Exist(go))
    {
        shopUiObjects.push_back(go);
    }
    return go;
}

bool ShopTap::Exist(GameObject* go)
{
    for (auto& m : shopUiObjects)
    {
        if (m == go)
        {
            return true;
        }
    }
    return false;
}

void ShopTap::Init()
{
    for (auto i : shopUiObjects)
    {
        i->Init();
    }

    SetPlayerInfo();
}

void ShopTap::Reset()
{
    for (auto i : shopUiObjects)
    {
        i->Reset();
    }

    // SHOP TAP
    {
        sf::Vector2f size = FRAMEWORK.GetWindowSize();

        pierrePortrait.SetOrigin(Origins::TR);
        pierrePortrait.SetScale(4.f, 4.f);
        pierrePortrait.SetPosition(size.x/4.f, 100.f);
        pierreTextBox.SetSize({ pierrePortrait.sprite.getGlobalBounds().width, pierrePortrait.sprite.getGlobalBounds(). height});
        pierreTextBox.SetOrigin(Origins::TR);
        pierreTextBox.SetPosition(size.x / 4.f, pierrePortrait.GetPosition().y + pierrePortrait.sprite.getGlobalBounds().height + 10.f);

        StringTable* stringTable1 = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);

        pierreText.SetString(stringTable1->Get("PIERRE"));
        pierreText.SetOrigin(Origins::TR);
        //pierreText.
    }
}

void ShopTap::Release()
{
    for (auto it : shopSlot)
    {
        delete it;
    }

    shopUiObjects.clear();
}

void ShopTap::Update(float dt)
{
    for (auto i : shopUiObjects)
    {
        i->Update(dt);
    }

    PlayerInfoUpdate();
}

void ShopTap::Draw(sf::RenderWindow& window)
{
    SortGos();

    for (auto m : shopUiObjects)
    {
        if (m->GetActive())
        {
            m->Draw(window);
        }
    }

    //window.setView(shopTapView);
    for (auto m : shopUiObjects)
    {
        if (m->GetActive())
        {
            m->Draw(window);
        }
    }
}

void ShopTap::SortGos()
{
    shopUiObjects.sort([](GameObject* lhs, GameObject* rhs) {
        if (lhs->sortLayer != rhs->sortLayer)
            return lhs->sortLayer < rhs->sortLayer;
        return lhs->sortOrder < rhs->sortOrder;
        });
}

void ShopTap::SetPlayerInfo()
{
    playerItemList = player->GetPlayerItemList();
    moneyInt = player->GetMoney();
}

void ShopTap::PlayerInfoUpdate()
{
    std::stringstream ss;
    ss << *moneyInt;
    moneyText.SetString(ss.str()); // 현재 소지금
}