#include "stdafx.h"
#include "Shop.h"
#include "ShopSlot.h"

Shop::Shop(const std::string& n)
	: GameObject(n),
    pierre("graphics/pierrePortrait.png", "pierrePortrait"),
    pierreText("pierreText", "fonts/SDMiSaeng.ttf"),
    pierreTextBox("graphics/box1.png", "pierreTextBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE),
    shopBox("graphics/box1.png", "pierreTextBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE),
    moneyBar("graphics/Cursors.ko-KR.png", "moneyBar", "money"),
    moneyText("moneyText", "fonts/SDMiSaeng.ttf"),
    xButton("graphics/Cursors.ko-KR.png", "xButton", "xButton"),
    invenBox("graphics/box1.png", "shopInvenBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE)
{
    AddUi(&pierre);
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

Shop::~Shop()
{
    Release();
}

GameObject* Shop::AddUi(GameObject* go)
{
    if (!Exist(go))
    {
        shopUiObjects.push_back(go);
    }
    return go;
}

bool Shop::Exist(GameObject* go)
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

void Shop::Init()
{
    for (auto i : shopUiObjects)
    {
        i->Init();
    }

    moneyInt = player->GetMoney();
}

void Shop::Reset()
{
    for (auto i : shopUiObjects)
    {
        i->Reset();
    }
}

void Shop::Release()
{
    for (auto it : shopSlot)
    {
        delete it;
    }

    shopUiObjects.clear();
}

void Shop::Update(float dt)
{
    for (auto i : shopUiObjects)
    {
        i->Update(dt);
    }
}

void Shop::Draw(sf::RenderWindow& window)
{
    SortGos();

    for (auto m : shopUiObjects)
    {
        if (m->GetActive())
        {
            m->Draw(window);
        }
    }
}

void Shop::SortGos()
{
    shopUiObjects.sort([](GameObject* lhs, GameObject* rhs) {
        if (lhs->sortLayer != rhs->sortLayer)
            return lhs->sortLayer < rhs->sortLayer;
        return lhs->sortOrder < rhs->sortOrder;
        });
}

void Shop::PlayerInfoUpdate()
{
    std::stringstream ss;
    ss << *moneyInt;
    moneyText.SetString(ss.str()); // 현재 소지금
}
