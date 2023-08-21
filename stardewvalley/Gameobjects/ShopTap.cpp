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
    scrollBg("graphics/scrollBg.png", "scrollBg", {2, 2, 2, 2}, {0,0,6,6}, NINE_SLICE),
    scrollBar("graphics/Cursors.ko-KR.png", "scrollBar", "scrollBar"),
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
    AddUi(&scrollBg);
    AddUi(&scrollBar);
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
        wstring pierreVerse1 = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String)->GetUni("PIERRE1", Languages::KOR);
        pierreText1.SetText(pierreVerse1, 50, sf::Color::Black, Origins::TL, 100, pierreTextBox.vertexArray[0].position.x + 30.f, pierreTextBox.GetPosition().y + 20.f);
        wstring pierreVerse2 = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String)->GetUni("PIERRE2", Languages::KOR);
        pierreText2.SetText(pierreVerse2, 50, sf::Color::Black, Origins::TL, 100, pierreText1.GetPosition().x, pierreText1.GetPosition().y + 50.f);
        wstring pierreVerse3 = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String)->GetUni("PIERRE3", Languages::KOR);
        pierreText3.SetText(pierreVerse3, 50, sf::Color::Black, Origins::TL, 100, pierreText1.GetPosition().x, pierreText2.GetPosition().y + 50.f);
        wstring pierreVerse4 = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String)->GetUni("PIERRE4", Languages::KOR);
        pierreText4.SetText(pierreVerse4, 50, sf::Color::Black, Origins::TL, 100, pierreText1.GetPosition().x, pierreText3.GetPosition().y + 50.f);

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
            shopSlot[i]->SetPosition(shopSlotPos.x + 15.f, shopSlotPos.y + 15.f +  i*shopSlot[i]->cellBox.GetSize().y);
            shopSlot[i]->SetActive(false);
        }
    }

    // SCROLL
    {
        scrollUp.SetOrigin(Origins::TC);
        scrollUp.SetPosition(shopBox.GetPosition().x + shopBox.GetSize().x + 50.f, shopBox.GetPosition().y);

        scrollBar.SetScale(4.f, 4.f);
        scrollBar.SetOrigin(Origins::TC);
        scrollBar.SetPosition(scrollUp.GetPosition().x, scrollUp.GetPosition().y + scrollUp.sprite.getGlobalBounds().height + 10.f);

        scrollDown.SetOrigin(Origins::BC);
        scrollDown.SetPosition(scrollUp.GetPosition().x, invenBox.vertexArray[35].position.y);

        scrollBg.SetSize({ scrollBar.sprite.getGlobalBounds().width, (scrollDown.GetPosition().y - scrollDown.sprite.getGlobalBounds().height - 10.f) - scrollBar.GetPosition().y });
        scrollBg.SetOrigin(Origins::TC);
        scrollBg.SetPosition(scrollBar.GetPosition());

        // MASK
        shopBoxMask.create(shopBox.GetPosition().x + shopBox.GetSize().x - 15.f, shopBox.GetPosition().y + shopBox.GetSize().y - 15.f);
        //shopBoxMask.create(FRAMEWORK.GetWindowSize().x, FRAMEWORK.GetWindowSize().y);
        shopBoxMask.clear(sf::Color::Transparent);

        sf::Texture texture;
        texture.loadFromFile("graphics/shopCellBox.png");
        for (int i = 0; i < shopSlot.size(); ++i)
        {
            shopBoxMask.draw(shopSlot[i]->cellBox.vertexArray, &texture);
            shopBoxMask.draw(shopSlot[i]->iconCell.sprite);
            shopBoxMask.draw(shopSlot[i]->itemIcon.sprite);
            shopBoxMask.draw(shopSlot[i]->itemText.text);
            shopBoxMask.draw(shopSlot[i]->coin.sprite);
            shopBoxMask.draw(shopSlot[i]->coinText.text);
        }
        shopBoxMask.display();

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
    if (shopSlot[0]->GetActive())
    {
        sf::Sprite m(shopBoxMask.getTexture());
        window.draw(m);
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
        for (auto i : shopSlot)
        {
            i->SetActive(true);
        }
    }

    else
    {
        for (auto i : shopUiObjects)
        {
            i->SetActive(false);
        }
        for (auto i : shopSlot)
        {
            i->SetActive(false);
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

    // SCROLL : 여기는 드래그라서 수정해야 함 ㅠㅠ
    {
        scrollBar.OnClick = [this]() {

        };

        scrollUp.OnClick = [this]() {

        };

        scrollDown.OnClick = [this]() {

        };
    }
}
