#include "stdafx.h"
#include "ShopTap.h"
#include "ShopSlot.h"
#include "Wall.h"
#include "Framework.h"
#include "SceneMgr.h"
#include "Framework.h"
#include "StringTable.h"
#include "AllItemTable.h"
#include "DataTableMgr.h"
#include "ShopInvenSlot.h"
#include "Utils.h"
#include "InputMgr.h"

ShopTap::ShopTap(const std::string& n)
	: GameObject(n),
    pierrePortrait("graphics/pierrePortrait.png", "pierrePortrait"),
    pierreText1("pierreText1", "fonts/SDMiSaeng.ttf"),
    pierreText2("pierreText2", "fonts/SDMiSaeng.ttf"),
    pierreText3("pierreText3", "fonts/SDMiSaeng.ttf"),
    pierreText4("pierreText4", "fonts/SDMiSaeng.ttf"),
    pierreTextBox("graphics/box1.png", "pierreTextBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE),
    shopBox("graphics/box1.png", "pierreTextBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE),
    moneyBar("graphics/Cursors.ko-KR.png", "moneyBar", "money"),
    moneyText("moneyText", "fonts/SDMiSaeng.ttf"),
    xButton("graphics/Cursors.ko-KR.png", "xButton", "xButton"),
    invenBox("graphics/box1.png", "shopInvenBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE),
    scrollUp("graphics/Cursors.ko-KR.png", "arrowUp", "arrowUp"),
    scrollDown("graphics/Cursors.ko-KR.png", "arrowDown", "arrowDown")
{
    // SHOP TAP
    AddUi(&pierrePortrait);
    AddUi(&pierreText1);
    AddUi(&pierreText2);
    AddUi(&pierreText3);
    AddUi(&pierreText4);
    AddUi(&pierreTextBox);
    AddUi(&shopBox);
    AddUi(&moneyBar);
    AddUi(&moneyText);
    AddUi(&xButton);
    AddUi(&invenBox);
    AddUi(&scrollUp);
    AddUi(&scrollDown);
    
    int itemNum = 9;
    for (int i = 0; i < shopSlotCount; ++i)
    {
        std::string num = to_string(i);

        shopSlot.push_back(new ShopSlot((ItemId)itemNum, "graphics/shopCellBox.png", "shopCellBox" + num, { 27,27,26,26 }, {0,0,80,80}, NINE_SLICE));
        shopSlot[i]->shopSlotIndex = i;
        shopSlot[i]->SetOrigin(Origins::MC);
        //AddUi(shopSlot[i]);
        itemNum++;
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            std::string num = to_string((i * 12) + j);
            shopInvenSlot.push_back(new ShopInvenSlot("graphics/MenuTiles.png", "invenCell" + num, "invenCell"));
            shopInvenSlot[(i * 12) + j]->slotIndex = (i * 12) + j;
            shopInvenSlot[(i * 12) + j]->SetOrigin(Origins::MC);
            shopInvenSlot[(i * 12) + j]->colliderOnOff = false;
            AddUi(shopInvenSlot[i * 12 + j]);
        }
    }
    prevLang = Variables::CurrentLang;
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
    InitInfo();
    ButtonSetUp();

    for (auto i : shopUiObjects)
    {
        i->Init();
    }
}

void ShopTap::Reset()
{
    for (auto i : shopUiObjects)
    {
        i->Reset();
    }
    for (auto i : shopUiObjects)
    {
        i->SetActive(false);
    }
    // BASE
    {
        sf::Vector2f size = FRAMEWORK.GetWindowSize();

        // PIERRE PORTRAIT
        pierrePortrait.SetOrigin(Origins::TR);
        pierrePortrait.SetScale(4.f, 4.f);
        pierrePortrait.SetPosition(size.x/7.f + 100.f, 100.f);
        pierrePortrait.colliderOnOff = false;

        // PIERRE TEXTBOX
        pierreTextBox.SetSize({ pierrePortrait.sprite.getGlobalBounds().width, pierrePortrait.sprite.getGlobalBounds(). height - 40.f});
        pierreTextBox.SetOrigin(Origins::TR);
        pierreTextBox.SetPosition(pierrePortrait.GetPosition().x, pierrePortrait.GetPosition().y + pierrePortrait.sprite.getGlobalBounds().height + 10.f);

        // PIERRE WORD
        string pierreVerse1 = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String)->Get("PIERRE1");
        string pierreVerse2 = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String)->Get("PIERRE2");
        string pierreVerse3 = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String)->Get("PIERRE3");
        string pierreVerse4 = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String)->Get("PIERRE4");
        pierreText1.SetText(pierreVerse1 + "\n" + pierreVerse2 + "\n" + pierreVerse3 + "\n" + pierreVerse4, 50, sf::Color::Black, Origins::TL, 100, pierreTextBox.vertexArray[0].position.x + 30.f, pierreTextBox.GetPosition().y + 20.f);

        // SHOP BOX
        shopBox.SetSize({ size.x / 1.5f, 120.f*4.f });
        shopBox.SetOrigin(Origins::TL);
        shopBox.SetPosition(pierrePortrait.GetPosition().x + 10.f, pierrePortrait.GetPosition().y);

        // MONEY BAR
        moneyBar.SetOrigin(Origins::TL);
        moneyBar.SetScale(4.5f, 4.5f);
        moneyBar.SetPosition(shopBox.GetPosition().x, shopBox.vertexArray[34].position.y);
        moneyBar.colliderOnOff = false;

        // MONEY TEXT
        std::stringstream ss;
        ss << *moneyInt;
        moneyText.SetText(ss.str(), 50, sf::Color::Black, Origins::TR, 100, moneyBar.GetPosition().x + moneyBar.sprite.getGlobalBounds().width - 50.f, moneyBar.GetPosition().y + 10.f);

        // XBUTTON
        xButton.SetOrigin(Origins::MC);
        xButton.SetScale(4.f, 4.f);
        xButton.SetPosition(shopBox.vertexArray[9].position);
        xButton.colliderOnOff = false;

        // INVEN BOX
        invenBox.SetSize({ 1040.f / 1.1f, 670.f / (1.1f * 2.f) - 20.f });
        invenBox.SetOrigin(Origins::TR);
        invenBox.SetPosition(shopBox.vertexArray[34].position.x, shopBox.vertexArray[34].position.y + 10.f);
    }

    // SLOT
    {
        // SHOP INVEN SLOT
        sf::Vector2f invenSlotPos = { invenBox.vertexArray[0].position + sf::Vector2f{ 80.f, 80.f } / 1.1f };
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 12; ++j)
            {
                shopInvenSlot[(i * 12) + j]->SetScale(0.9f, 0.9f);
                shopInvenSlot[(i * 12) + j]->SetPosition(invenSlotPos.x + (j * 80.f / 1.1f), invenSlotPos.y + (i * 80.f / 1.1f));
            }
        }

        // SHOP SLOT
        sf::Vector2f shopSlotPos = { shopBox.vertexArray[0].position };
        for (int i = 0; i < shopSlotCount; ++i)
        {
            shopSlot[i]->Init();
            shopSlot[i]->Reset();
            shopSlot[i]->cellBox.SetSize({ shopBox.GetSize().x - 30.f, (shopBox.GetSize().y - 30.f) / 4.f });
            shopSlot[i]->SetOrigin(Origins::TL);
            shopSlot[i]->SetPosition(shopSlotPos.x + 15.f, shopSlotPos.y + 15.f +  (i%4)*shopSlot[0]->cellBox.GetSize().y);
            shopSlot[i]->SetActive(false);
        }
    }

    // SCROLL
    {
        scrollUp.SetOrigin(Origins::TC);
        scrollUp.SetPosition(shopBox.GetPosition().x + shopBox.GetSize().x + 50.f, shopBox.GetPosition().y);

        scrollDown.SetOrigin(Origins::BC);
        scrollDown.SetPosition(scrollUp.GetPosition().x, shopBox.vertexArray[35].position.y);
    }
}

void ShopTap::Release()
{
    for (auto it : shopSlot)
    {
        delete it;
    }

    for (auto it : shopInvenSlot)
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

    sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
    sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);
    sf::Vector2f boxPos = shopBox.GetPosition();
    if (uiMousePos.x >= boxPos.x && uiMousePos.x <= boxPos.x + shopBox.GetSize().x && uiMousePos.y >= boxPos.y && uiMousePos.y <= boxPos.y + shopBox.GetSize().y - 15.f)
    {
        for (int i = 0; i < shopSlot.size(); ++i)
        {
            shopSlot[i]->Update(dt);
        }
    }

    PlayerInfoUpdate();
    IconUpdate();
    ItemIndexUpdate();

    if (Variables::CurrentLang != prevLang)
    {
        Reset();
    }
    prevLang = Variables::CurrentLang;
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

    for (auto i : shopSlot)
    {
        if (i->GetActive())
        {
            i->Draw(window);
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

void ShopTap::InitInfo()
{
    playerItemList = player->GetPlayerItemList();
    moneyInt = player->GetMoney();
    tempMoney = player->GetTempMoney();
    itemIconList = inven->GetItemIconList();
}

void ShopTap::PlayerInfoUpdate()
{
    std::stringstream ss;
    ss.str("");
    ss << *moneyInt;
    moneyText.SetString(ss.str()); // 현재 소지금
}

void ShopTap::IconUpdate()
{
    int num = 0;

    for (ShopInvenSlot* sl : shopInvenSlot)
    {
        for (tagItemInfo& pl : *playerItemList)
        {
            if (pl.index == sl->slotIndex)
            {
                auto foundItem = itemIconList->find(pl.itemId);
                if (foundItem != itemIconList->end())
                {
                    sl->SetItemIcon(&(foundItem->second));
                    sl->SetItemId(pl.itemId);
                    sl->GetItemIcon()->SetScale(4.f, 4.f);
                    break;
                }
            }
            else
            {
                sl->SetItemIcon(nullptr);
                sl->SetItemId(ItemId::none);
            }
        }
    }
}

void ShopTap::ItemIndexUpdate()
{
    for (tagItemInfo& pl : *playerItemList)
    {
        for (ShopInvenSlot* sl : shopInvenSlot)
        {
            if (pl.itemId == sl->GetItemId())
            {
                pl.index = sl->slotIndex;
                continue;
            }
        }
    }
}

void ShopTap::TapOnOff()
{
    if (shopTapOn)
    {
        for (auto i : shopUiObjects)
        {
            i->SetActive(true);
        }
        for (int i = 0; i<shopSlot.size(); ++i)
        {
            if (i == 4)
            {
                break;
            }
            shopSlot[i]->SetActive(true);
        }
    }
    else
    {
        for (auto i : shopUiObjects)
        {
            i->SetActive(false);
        }
        for (int i = 0; i < shopSlot.size(); ++i)
        {
            shopSlot[i]->SetActive(false);
        }
    }
}

void ShopTap::ButtonSetUp()
{
    for (int i = 0; i< shopSlot.size(); ++i)
    {
        shopSlot[i]->OnClick = [this, i]() {
            const ItemInfo* item = DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem)->Get(shopSlot[i]->GetItemId());
            if (*player->GetMoney() >= item->price)
            {
                *tempMoney = -item->price;
                player->AddPlayerItem(shopSlot[i]->GetItemId());
            }
        };
    }

    for (int i = 0; i < shopInvenSlot.size(); ++i)
    {
        shopInvenSlot[i]->OnClick = [this, i]() {
            const ItemInfo* item = DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem)->Get(shopInvenSlot[i]->GetItemId());
            if (item == nullptr || item->price == 0)
            {
                return;
            }
            if (player->RemovePlayerItem(shopInvenSlot[i]->GetItemId()))
            {
                *tempMoney = item->price / 2.f;
            }
        };
    }

    xButton.OnClick = [this]() {
        shopTapOn = false;
        TapOnOff();
    };

    pierre->OnClickWorld = [this]() {
        if (Utils::Distance(player->GetPosition(), pierre->GetPosition()) < 200.f)
        {
            shopTapOn = true;
            TapOnOff();
            // TEST CODE
           /* shopSlot[4]->SetActive(false);
            shopSlot[5]->SetActive(false);
            shopSlot[6]->SetActive(false);
            shopSlot[7]->SetActive(false);
            shopSlot[8]->SetActive(false);
            shopSlot[9]->SetActive(false);*/
        }
    };

    // SCROLL
    {
        scrollUp.OnClick = [this]() {
            if (shopSlot[4]->GetActive())
            {
                for (int i = 0; i < shopSlot.size(); ++i)
                {
                    if (i >= 0 && i <= 3)
                    {
                        shopSlot[i]->SetActive(true);
                    }
                    else
                    {
                        shopSlot[i]->SetActive(false);
                    }
                }
            }
            if (shopSlot[8]->GetActive())
            {
                for (int i = 0; i < shopSlot.size(); ++i)
                {
                    if (i >= 4 && i <= 7)
                    {
                        shopSlot[i]->SetActive(true);
                    }
                    else
                    {
                        shopSlot[i]->SetActive(false);
                    }
                }
            }
            if (shopSlot[12]->GetActive())
            {
                for (int i = 0; i < shopSlot.size(); ++i)
                {
                    if (i >= 8 && i <= 11)
                    {
                        shopSlot[i]->SetActive(true);
                    }
                    else
                    {
                        shopSlot[i]->SetActive(false);
                    }
                }
            }
        };

        scrollDown.OnClick = [this]() {
            if (shopSlot[0]->GetActive())
            {
                for (int i = 0; i < shopSlot.size(); ++i)
                {
                    if (i >= 4 && i <= 7)
                    {
                        shopSlot[i]->SetActive(true);
                    }
                    else
                    {
                        shopSlot[i]->SetActive(false);
                    }
                }
            }
            else if (shopSlot[4]->GetActive())
            {
                for (int i = 0; i < shopSlot.size(); ++i)
                {
                    if (i >= 8 && i <= 11)
                    {
                        shopSlot[i]->SetActive(true);
                    }
                    else
                    {
                        shopSlot[i]->SetActive(false);
                    }
                }
            }
            else if (shopSlot[8]->GetActive())
            {
                for (int i = 0; i < shopSlot.size(); ++i)
                {
                    if (i == 12)
                    {
                        shopSlot[i]->SetActive(true);
                    }
                    else
                    {
                        shopSlot[i]->SetActive(false);
                    }
                }
            }
        };
    }
}
