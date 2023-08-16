#include "stdafx.h"
#include "Inventory.h"
#include "InputMgr.h"
#include "DataTableMgr.h"
#include "StringTable.h"
#include "ResourceMgr.h"
#include "AllItemTable.h"
#include "Slot.h"
#include "SceneMgr.h"

GameObject* Inventory::AddUi(GameObject* go)
{
    if (!Exist(go))
    {
        invenUiObjects.push_back(go);
    }
    return go;
}

bool Inventory::Exist(GameObject* go)
{
    for (auto& m : invenUiObjects)
    {
        if (m == go)
        {
            return true;
        }
    }
    return false;
}

Inventory::Inventory(const std::string& n)
    : GameObject(n), invenBox("graphics/box1.png", "invenBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE),
    invenLine("graphics/invenBoxLine.png", "invenBoxLine", { 24,0,52,27 }, { 0,0,100,27 }, THREE_SLICE),
    bag("graphics/Cursors.ko-KR.png", "invenBag", "invenBag"),
    map("graphics/Cursors.ko-KR.png", "invenMap", "invenMap"),
    make("graphics/Cursors.ko-KR.png", "invenMake", "invenMake"),
    changeScene("graphics/Cursors.ko-KR.png", "invenSetting", "invenSetting"),
    xButton("graphics/Cursors.ko-KR.png", "xButton", "xButton"),
    title("graphics/setButton.png", "title"),
    end("graphics/setButton.png", "end"),
    mapImage("graphics/map.png", "map", "map"),
    ring("graphics/MenuTiles.png", "invenRing", "invenRing"),
    shoes("graphics/MenuTiles.png", "invenShoes", "invenShoes"),
    hat("graphics/MenuTiles.png", "invenHat", "invenHat"),
    charBg("graphics/daybg.png", "charBg"),
    curFunds("curFunds", "fonts/SDMiSaeng.ttf"),
    curFundsValue("curFundsValue", "fonts/SDMiSaeng.ttf"),
    totalEarnings("totalEarnings", "fonts/SDMiSaeng.ttf"),
    totalEarningsValue("totalEarnings", "fonts/SDMiSaeng.ttf")
{
    AddUi(&invenBox);
    AddUi(&invenLine);
    AddUi(&bag);
    AddUi(&map);
    AddUi(&make);
    AddUi(&changeScene);
    AddUi(&xButton);
    AddUi(&mapImage);
    AddUi(&ring);
    AddUi(&shoes);
    AddUi(&hat);
    AddUi(&charBg);
    AddUi(&curFunds);
    AddUi(&totalEarnings);
    AddUi(&curFundsValue);
    AddUi(&totalEarningsValue);
    AddUi(&pl);
    AddUi(&title);
    AddUi(&end);

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            std::string num = to_string((i * 12) + j);
            slot.push_back(new Slot("graphics/MenuTiles.png", "invenCell" + num, "invenCell"));
            slot[(i * 12) + j]->slotIndex = (i * 12) + j;
            slot[(i * 12) + j]->SetOrigin(Origins::MC);
            slot[(i * 12) + j]->colliderOnOff = false;
            AddUi(slot[i * 12 + j]);
        }
    }

    mouseSlot = (Slot*)AddUi(new Slot());
}

Inventory::~Inventory()
{
    for (auto it = invenUiObjects.begin(); it != invenUiObjects.end(); ++it)
    {
        delete *it;
    }
    invenUiObjects.clear();
}

void Inventory::Init()
{
    ////처음 클릭
    //tagItemInfo onMouseItem;
    //onMouseItem = item[0];
    //item[0] = empty;

    ////빈공간 다시 클릭
    //item[3] = onMouseItem;
    //onMouseItem = empty;

    ////이미 있는 공간 클릭
    //tagItemInfo tempItem;
    //tempItem = item[3];

    //item[3] = onMouseItem;
    //onMouseItem = tempItem;

    curFundsInt = player->GetMoney();
    totalEarningsInt = player->GetTotalEarningsInt();
    SetPlayerItemList();
    PlayerInfoUpdate();
    ItemIconSetUp();
    ButtonSetUp();

    for (auto i : invenUiObjects)
    {
        i->Init();
    }
}

void Inventory::Reset()
{
    for (auto m : invenUiObjects)
    {
        m->Reset();
    }

    // 오브젝트 초기 세팅
    {
        invenBox.SetSize({ 1040.f, 670.f });
        invenBox.SetOrigin(Origins::MC);
        invenBox.SetPosition(position);
        invenBox.sortLayer = (int)UiType::BOX;

        slotPos = { invenBox.vertexArray[0].position.x + 80.f, invenBox.vertexArray[0].position.y + 100.f };
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 12; ++j)
            {
                slot[(i * 12) + j]->SetPosition(slotPos.x + (j * 80.f), slotPos.y + (i * 80.f));
                slot[(i * 12) + j]->sortLayer = (int)UiType::LINE;
                slot[(i * 12) + j]->SetMouseIcon(mouseSlot);
            }
        }

        invenLine.SetSize(1040.f);
        invenLine.SetOrigin(Origins::MC);
        invenLine.SetPosition(position.x, slot[35]->GetPosition().y + 80.f);
        invenLine.sortLayer = (int)UiType::LINE;

        bagPos = { invenBox.vertexArray[0].position + sf::Vector2f{10.f, 0.f} };
        bag.SetScale(4.f, 4.f);
        bag.SetOrigin(Origins::BL);
        bag.SetPosition(bagPos);
        bag.colliderOnOff = false;
        bag.sortLayer = (int)UiType::BUTTON;

        float buttonW = bag.sprite.getGlobalBounds().width;
        mapPos = { bagPos.x + buttonW, bagPos.y };
        map.SetScale(4.f, 4.f);
        map.SetOrigin(Origins::BL);
        map.SetPosition(mapPos);
        map.colliderOnOff = false;
        map.sortLayer = (int)UiType::BUTTON;

        makePos = { mapPos.x + buttonW, mapPos.y };
        make.SetScale(4.f, 4.f);
        make.SetOrigin(Origins::BL);
        make.SetPosition(makePos);
        make.colliderOnOff = false;
        make.sortLayer = (int)UiType::BUTTON;

        changeScenePos = { makePos.x + buttonW, makePos.y };
        changeScene.SetScale(4.f, 4.f);
        changeScene.SetOrigin(Origins::BL);
        changeScene.SetPosition(changeScenePos);
        changeScene.colliderOnOff = false;
        changeScene.sortLayer = (int)UiType::BUTTON;

        xButtonPos = { invenBox.vertexArray[9].position };
        xButton.SetScale(4.f, 4.f);
        xButton.SetOrigin(Origins::BL);
        xButton.SetPosition(xButtonPos);
        xButton.colliderOnOff = false;
        xButton.sortLayer = (int)UiType::COMMON;

        mapImage.SetScale(4.5f, 4.5f);
        mapImage.SetOrigin(Origins::MC);
        mapImage.SetPosition(position);
        mapImage.colliderOnOff = false;
        mapImage.sortLayer = (int)UiType::MAP;

        ring.SetOrigin(Origins::MC);
        ring.SetPosition(slot[0]->GetPosition().x, invenLine.GetPosition().y + 80.f);
        ring.colliderOnOff = false;
        ring.sortLayer = (int)UiType::ITEM;

        shoes.SetOrigin(Origins::MC);
        shoes.SetPosition(slot[0]->GetPosition().x, ring.GetPosition().y + 80.f);
        shoes.colliderOnOff = false;
        shoes.sortLayer = (int)UiType::ITEM;

        hat.SetOrigin(Origins::MC);
        hat.SetPosition(slot[0]->GetPosition().x, shoes.GetPosition().y + 80.f);
        hat.colliderOnOff = false;
        hat.sortLayer = (int)UiType::ITEM;

        charBg.SetScale(1.25f, 1.25f);
        charBg.SetOrigin(Origins::MC);
        charBg.SetPosition(shoes.GetPosition().x + 140.f, shoes.GetPosition().y);
        charBg.colliderOnOff = false;
        charBg.sortLayer = (int)UiType::ITEM;

        StringTable* stringTable1 = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);
        curFunds.SetString(stringTable1->Get("CUR_MONEY"));
        curFunds.text.setCharacterSize(60);
        curFunds.text.setFillColor(sf::Color::Black);
        curFunds.SetPosition(charBg.GetPosition().x + 500.f, charBg.GetPosition().y - 40.f);
        curFunds.SetOrigin(Origins::MR);
        curFunds.sortLayer = (int)UiType::ITEM;

        std::stringstream ss;
        ss << *curFundsInt;
        curFundsValue.SetString(ss.str());
        curFundsValue.text.setCharacterSize(60);
        curFundsValue.text.setFillColor(sf::Color::Black);
        curFundsValue.SetPosition(curFunds.GetPosition().x + 50.f, curFunds.GetPosition().y);
        curFundsValue.SetOrigin(Origins::ML);
        curFundsValue.sortLayer = (int)UiType::ITEM;

        totalEarnings.SetString(stringTable1->Get("TOTAL_MONEY"));
        totalEarnings.text.setCharacterSize(60);
        totalEarnings.text.setFillColor(sf::Color::Black);
        totalEarnings.SetPosition(charBg.GetPosition().x + 500.f, charBg.GetPosition().y + 30.f);
        totalEarnings.SetOrigin(Origins::MR);
        totalEarnings.sortLayer = (int)UiType::ITEM;

        ss.str("");
        ss << *totalEarningsInt;
        totalEarningsValue.SetString(ss.str());
        totalEarningsValue.text.setCharacterSize(60);
        totalEarningsValue.text.setFillColor(sf::Color::Black);
        totalEarningsValue.SetPosition(totalEarnings.GetPosition().x + 50.f, totalEarnings.GetPosition().y);
        totalEarningsValue.SetOrigin(Origins::ML);
        totalEarningsValue.sortLayer = (int)UiType::ITEM;

        title.text.setFont(*RESOURCE_MGR.GetFont("fonts/SDMiSaeng.ttf"));
        title.text.setString(stringTable1->Get("TOTITLE"));
        title.text.setCharacterSize(100);
        title.text.setFillColor(sf::Color::Black);
        title.SetPosition(position.x, position.y - 80.f);
        title.text.setPosition(title.GetPosition().x, title.GetPosition().y - 40.f);
        title.SetScale(1.5f, 1.5f);
        title.SetOrigin(Origins::MC);
        title.sortLayer = (int)UiType::CHANEGE;

        end.text.setFont(*RESOURCE_MGR.GetFont("fonts/SDMiSaeng.ttf"));
        end.text.setString(stringTable1->Get("END"));
        end.text.setCharacterSize(100);
        end.text.setFillColor(sf::Color::Black);
        end.SetPosition(title.GetPosition().x,title.GetPosition().y + title.sprite.getGlobalBounds().height + 30.f);
        end.text.setPosition(end.GetPosition().x, end.GetPosition().y - 40.f);
        end.SetScale(1.5f, 1.5f);
        end.SetOrigin(Origins::MC);
        end.sortLayer = (int)UiType::CHANEGE;

        player->GetAnimation().Play("Idle");
        pl.sprite = player->sprite;
        pl.SetOrigin(Origins::MC);
        pl.SetPosition(charBg.GetPosition());
        pl.sortLayer = (int)UiType::ITEM;

        mouseSlot->sortLayer = (int)UiType::ITEM;
        mouseSlot->sortOrder = 2;
    }

    SetWindowClear();
}

void Inventory::Release()
{
}

void Inventory::Update(float dt)
{
    for (auto m : invenUiObjects)
    {
        m->Update(dt);
    }
    PlayerInfoUpdate();

    // 인벤창 여닫기
    if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
    {
        if (!invenOnOff)
        {
            SetItemWindow();
            IconUpdate();
            invenOnOff = true;
        }
        else if(mouseSlot->GetItemIcon() == nullptr)
        {
            // 창 닫을 때마다 플레이어아이템인덱스 업데이트
            ItemIndexUpdate();
            SetWindowClear();
            IconUpdate();
            invenOnOff = false;
        }
    }

    // 마우스에 보이지 않는 슬롯 포지셔닝
    sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
    sf::Vector2f mPos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);
    mouseSlot->SetPosition(mPos);

    // 슬롯, 아이템 인덱스 동일화

}

void Inventory::Draw(sf::RenderWindow& window)
{
    SortGos();

    for (auto m : invenUiObjects)
    {
        if (m->GetActive())
        {
            m->Draw(window);
        }
    }
}

void Inventory::SetItemWindow()
{
    for (auto m : invenUiObjects)
    {
        if (m->sortLayer == (int)UiType::COMMON || m->sortLayer == (int)UiType::ITEM || m->sortLayer == (int)UiType::BUTTON || m->sortLayer == (int)UiType::BOX || m->sortLayer == (int)UiType::LINE || m->sortLayer == (int)UiType::TOOL)
        {
            m->SetActive(true);
        }
        else
        {
            m->SetActive(false);
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            slot[(i * 12) + j]->SetPosition(slotPos.x + (j * 80.f), slotPos.y + (i * 80.f));
        }
    }
    // 아이템도 보이도록 추가

    bag.SetPosition(bagPos.x, bagPos.y + 10.f);
    map.SetPosition(mapPos);
    make.SetPosition(makePos);
    changeScene.SetPosition(changeScenePos);
}

void Inventory::SetMapWindow()
{
    for (auto m : invenUiObjects)
    {
        if (m->sortLayer == (int)UiType::COMMON || m->sortLayer == (int)UiType::MAP)
        {
            m->SetActive(true);
        }
        else
        {
            m->SetActive(false);
        }
    }

    xButton.SetPosition(mapImage.GetPosition() + sf::Vector2f{mapImage.sprite.getGlobalBounds().width / 2.f, - mapImage.sprite.getGlobalBounds().height / 2.f});
}

void Inventory::SetMakeWindow()
{
    for (auto m : invenUiObjects)
    {
        if (m->sortLayer == (int)UiType::COMMON || m->sortLayer == (int)UiType::MAKE || m->sortLayer == (int)UiType::BUTTON || m->sortLayer == (int)UiType::BOX || m->sortLayer == (int)UiType::LINE || m->sortLayer == (int)UiType::TOOL)
        {
            m->SetActive(true);
        }
        else
        {
            m->SetActive(false);
        }
    }

    sf::Vector2f diff = { 0.f, invenLine.GetPosition().y - slot[0]->GetPosition().y + 80.f };

    for (int i = 0; i < slot.size(); ++i)
    {
        slot[i]->SetPosition(slot[i]->GetPosition() + diff);
    }

    make.SetPosition(makePos.x, makePos.y + 10.f);
    bag.SetPosition(bagPos);
    map.SetPosition(mapPos);
    changeScene.SetPosition(changeScenePos);
}

void Inventory::SetChangeSceneWindow()
{
    for (auto m : invenUiObjects)
    {
        if (m->sortLayer == (int)UiType::COMMON || m->sortLayer == (int)UiType::CHANEGE || m->sortLayer == (int)UiType::BUTTON || m->sortLayer == (int)UiType::BOX)
        {
            m->SetActive(true);
        }
        else
        {
            m->SetActive(false);
        }
    }

    xButton.SetPosition(invenBox.vertexArray[9].position);
    changeScene.SetPosition(changeScenePos.x, changeScenePos.y + 10.f);
    bag.SetPosition(bagPos);
    map.SetPosition(mapPos);
    make.SetPosition(makePos);
    xButton.SetPosition(xButtonPos);
}

void Inventory::SetWindowClear()
{
    for (auto& m : invenUiObjects)
    {
        m->SetActive(false);
    }
}

void Inventory::ButtonSetUp()
{
    bag.OnClick = [this]() {
        if (mouseSlot->GetItemIcon() == nullptr)
        {
            SetItemWindow();
        }
    };
    map.OnClick = [this]() {
        if (mouseSlot->GetItemIcon() == nullptr)
        {
            SetMapWindow();
        }
    };
    make.OnClick = [this]() {
        if (mouseSlot->GetItemIcon() == nullptr)
        {
            SetMakeWindow();
        }
    };
    changeScene.OnClick = [this]() {
        if (mouseSlot->GetItemIcon() == nullptr)
        {
            SetChangeSceneWindow();
        }
    };
    xButton.OnClick = [this]() {
        if (mouseSlot->GetItemIcon() == nullptr)
        {
            SetWindowClear();
        }
    };
}

void Inventory::SetPlayer(Player2* p)
{
    player = p;
}

void Inventory::PlayerInfoUpdate()
{
    std::stringstream ss;
    ss << *curFundsInt;
    curFundsValue.SetString(ss.str()); // 현재 소지금

    ss.str("");
    ss << *totalEarningsInt;
    totalEarningsValue.SetString(ss.str()); // 총합 자금
}

void Inventory::SortGos()
{
    invenUiObjects.sort([](GameObject* lhs, GameObject* rhs) {
        if (lhs->sortLayer != rhs->sortLayer)
            return lhs->sortLayer < rhs->sortLayer;
        return lhs->sortOrder < rhs->sortOrder;
        });
}

void Inventory::ItemIndexUpdate()
{
    for (tagItemInfo& pl : *playerItemList)
    {
        for (Slot* sl : slot)
        {
            if (pl.itemId == sl->GetItemId())
            {
                pl.index = sl->slotIndex;
                continue;
            }
        }
    }
}

void Inventory::ItemIconSetUp()
{
    AllItemTable* allItem = DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem);
    std::unordered_map<ItemId, ItemInfo>& item = allItem->table;
    for (auto& i : item)
    {
        itemIconList.insert({ i.first, SpriteGo(i.second.resource, i.second.name, i.second.nickName) });
    }

    for (auto& it : itemIconList)
    {
        it.second.Reset();
        it.second.colliderOnOff = false;
        it.second.SetOrigin(Origins::MC);
        it.second.SetScale(5.f, 5.f);
    }
}

void Inventory::IconUpdate()
{
    int num = 0;

    for (tagItemInfo& pl : *playerItemList)
    {
        for (Slot* sl : slot)
        {
            if (pl.index == sl->slotIndex)
            {
                auto foundItem = itemIconList.find(pl.itemId);
                if (foundItem != itemIconList.end())
                {
                    sl->SetItemIcon(&(foundItem->second));
                    sl->SetItemId(pl.itemId);
                    break;
                }
            }
        }
    }
}