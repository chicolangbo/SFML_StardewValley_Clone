#include "stdafx.h"
#include "Inventory.h"
#include "InputMgr.h"
#include "DataTableMgr.h"
#include "StringTable.h"

GameObject* Inventory::AddUi(GameObject* go)
{
    if (!Exist(go))
    {
        uiObjects.push_back(go);
    }
    return go;
}

GameObject* Inventory::AddUi2(UiType t, GameObject* go)
{
    if (!Exist2(go))
    {
        multiMap.insert(std::make_pair(t, go));
    }
    return nullptr;
}

bool Inventory::Exist(GameObject* go)
{
    return std::find(uiObjects.begin(), uiObjects.end(), go) != uiObjects.end();
}

bool Inventory::Exist2(GameObject* go)
{
    for (auto& m : multiMap)
    {
        if (m.second == go)
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

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            SpriteGo tempCell = SpriteGo("graphics/MenuTiles.png", "invenCell", "invenCell");
            cell.push_back(tempCell);
            cell[(i * 12) + j].SetOrigin(Origins::MC);
            cell[(i * 12) + j].colliderOnOff = false;
        }
    }

    tagItemInfo itemEmpty = { ITEM::ITEM_EMPTY ,"","",0,0,0 };
    tagItemInfo pick = { ITEM::ITEM_TOOL, "°î±ªÀÌ", "°î±ªÀÌ", 0, 0, 1 };
    tagItemInfo ax = { ITEM::ITEM_TOOL, "µµ³¢", "µµ³¢", 0, 0, 1 };
    tagItemInfo homi = { ITEM::ITEM_TOOL, "°î±ªÀÌ", "°î±ªÀÌ", 0, 0, 1 };
    tagItemInfo waterCan = { ITEM::ITEM_TOOL, "¹°»Ñ¸®°³", "¹°»Ñ¸®°³", 0, 0, 1 };
    tagItemInfo hook = { ITEM::ITEM_TOOL, "³´", "³´", 0, 0, 1 };
    addItem(pick);
    addItem(ax);
    addItem(homi);
    addItem(waterCan);
    addItem(hook);

    
    //AddUi(&invenBox);
    //AddUi(&invenLine);
    //AddUi(&bag);
    //AddUi(&map);
    //AddUi(&make);
    //AddUi(&changeScene);
    //AddUi(&xButton);
    //AddUi(&mapImage);
    //AddUi(&ring);
    //AddUi(&shoes);
    //AddUi(&hat);
    //AddUi(&charBg);
    //AddUi(&curFunds);
    //AddUi(&totalEarnings);
    //AddUi(&curFundsValue);
    //AddUi(&totalEarningsValue);

    // multiMap
    AddUi2(UiType::BOX, &invenBox);
    AddUi2(UiType::LINE, &invenLine);
    AddUi2(UiType::BUTTON, &bag);
    AddUi2(UiType::BUTTON, &map);
    AddUi2(UiType::BUTTON, &make);
    AddUi2(UiType::BUTTON, &changeScene);
    AddUi2(UiType::COMMON, &xButton);
    AddUi2(UiType::MAP, &mapImage);
    AddUi2(UiType::ITEM, &ring);
    AddUi2(UiType::ITEM, &shoes);
    AddUi2(UiType::ITEM, &hat);
    AddUi2(UiType::ITEM, &charBg);
    AddUi2(UiType::ITEM, &curFunds);
    AddUi2(UiType::ITEM, &totalEarnings);
    AddUi2(UiType::ITEM, &curFundsValue);
    AddUi2(UiType::ITEM, &totalEarningsValue);
}

Inventory::~Inventory()
{
}

void Inventory::addItem(tagItemInfo item)
{
    if (item.itemkind != ITEM::ITEM_EMPTY)
    {
        this->item.push_back(item);
    }
}

void Inventory::Init()
{
    ////Ã³À½ Å¬¸¯
    //tagItemInfo onMouseItem;
    //onMouseItem = item[0];
    //item[0] = empty;

    ////ºó°ø°£ ´Ù½Ã Å¬¸¯
    //item[3] = onMouseItem;
    //onMouseItem = empty;

    ////ÀÌ¹Ì ÀÖ´Â °ø°£ Å¬¸¯
    //tagItemInfo tempItem;
    //tempItem = item[3];

    //item[3] = onMouseItem;
    //onMouseItem = tempItem;

    //for (auto go : uiObjects)
    //{
    //    if (go->GetActive())
    //    {
    //        go->Init();
    //    }
    //}

    for (auto m : multiMap)
    {
        m.second->Init();
    }

    for (int i = 0; i < cell.size(); ++i)
    {
        cell[i].Init();
    }
}

void Inventory::Reset()
{
    for (auto m : multiMap)
    {
        m.second->Reset();
    }

    for (int i = 0; i < cell.size(); ++i)
    {
        cell[i].Reset();
    }

    // ¿ÀºêÁ§Æ® ÃÊ±â ¼¼ÆÃ
    {
        invenBox.SetSize({ 1040.f, 670.f });
        invenBox.SetOrigin(Origins::MC);
        invenBox.SetPosition(position);

        cellPos = { invenBox.vertexArray[0].position.x + 80.f, invenBox.vertexArray[0].position.y + 100.f };
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 12; ++j)
            {
                cell[(i * 12) + j].SetPosition(cellPos.x + (j * 80.f), cellPos.y + (i * 80.f));
            }
        }

        invenLine.SetSize(1040.f);
        invenLine.SetOrigin(Origins::MC);
        invenLine.SetPosition(position.x, cell[35].GetPosition().y + 80.f);

        bagPos = { invenBox.vertexArray[0].position + sf::Vector2f{10.f, 0.f} };
        bag.SetScale(4.f, 4.f);
        bag.SetOrigin(Origins::BL);
        bag.SetPosition(bagPos);
        bag.colliderOnOff = false;
        float buttonW = bag.sprite.getGlobalBounds().width;
        mapPos = { bagPos.x + buttonW, bagPos.y };
        map.SetScale(4.f, 4.f);
        map.SetOrigin(Origins::BL);
        map.SetPosition(mapPos);
        map.colliderOnOff = false;
        makePos = { mapPos.x + buttonW, mapPos.y };
        make.SetScale(4.f, 4.f);
        make.SetOrigin(Origins::BL);
        make.SetPosition(makePos);
        make.colliderOnOff = false;
        changeScenePos = { makePos.x + buttonW, makePos.y };
        changeScene.SetScale(4.f, 4.f);
        changeScene.SetOrigin(Origins::BL);
        changeScene.SetPosition(changeScenePos);
        changeScene.colliderOnOff = false;
        xButtonPos = { invenBox.vertexArray[9].position };
        xButton.SetScale(4.f, 4.f);
        xButton.SetOrigin(Origins::BL);
        xButton.SetPosition(xButtonPos);
        xButton.colliderOnOff = false;
        mapImage.SetScale(4.5f, 4.5f);
        mapImage.SetOrigin(Origins::MC);
        mapImage.SetPosition(position);
        mapImage.colliderOnOff = false;
        ring.SetOrigin(Origins::MC);
        ring.SetPosition(cell[0].GetPosition().x, invenLine.GetPosition().y + 80.f);
        ring.colliderOnOff = false;
        shoes.SetOrigin(Origins::MC);
        shoes.SetPosition(cell[0].GetPosition().x, ring.GetPosition().y + 80.f);
        shoes.colliderOnOff = false;
        hat.SetOrigin(Origins::MC);
        hat.SetPosition(cell[0].GetPosition().x, shoes.GetPosition().y + 80.f);
        hat.colliderOnOff = false;
        charBg.SetOrigin(Origins::MC);
        charBg.SetScale(1.25f, 1.25f);
        charBg.SetPosition(shoes.GetPosition().x + 140.f, shoes.GetPosition().y);
        charBg.colliderOnOff = false;
        StringTable* stringTable1 = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);
        curFunds.SetString(stringTable1->Get("CUR_MONEY"));
        curFunds.text.setCharacterSize(60);
        curFunds.text.setFillColor(sf::Color::Black);
        curFunds.SetPosition(charBg.GetPosition().x + 500.f, charBg.GetPosition().y - 40.f);
        curFunds.SetOrigin(Origins::MR);
        std::stringstream ss;
        ss << curFundsInt;
        curFundsValue.SetString(ss.str());
        curFundsValue.text.setCharacterSize(60);
        curFundsValue.text.setFillColor(sf::Color::Black);
        curFundsValue.SetPosition(curFunds.GetPosition().x + 50.f, curFunds.GetPosition().y);
        curFundsValue.SetOrigin(Origins::ML);
        totalEarnings.SetString(stringTable1->Get("TOTAL_MONEY"));
        totalEarnings.text.setCharacterSize(60);
        totalEarnings.text.setFillColor(sf::Color::Black);
        totalEarnings.SetPosition(charBg.GetPosition().x + 500.f, charBg.GetPosition().y + 30.f);
        totalEarnings.SetOrigin(Origins::MR);
        ss.str("");
        ss << totalEarningsInt;
        totalEarningsValue.SetString(ss.str());
        totalEarningsValue.text.setCharacterSize(60);
        totalEarningsValue.text.setFillColor(sf::Color::Black);
        totalEarningsValue.SetPosition(totalEarnings.GetPosition().x + 50.f, totalEarnings.GetPosition().y);
        totalEarningsValue.SetOrigin(Origins::ML);
    }

    SetWindowClear();
    ButtonSetUp();
}

void Inventory::Update(float dt)
{
    //for (auto go : uiObjects)
    //{
    //    if (go->GetActive())
    //    {
    //        go->Update(dt);
    //    }
    //}

    for (auto m : multiMap)
    {
        m.second->Update(dt);
    }

    if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
    {
        SetItemWindow();
    }
}

void Inventory::Draw(sf::RenderWindow& window)
{
    //for (auto go : uiObjects)
    //{
    //    if (go->GetActive())
    //    {
    //        go->Draw(window);
    //    }
    //}

    for (auto m : multiMap)
    {
        if (m.second->GetActive())
        {
            m.second->Draw(window);
        }
    }

    for (int i = 0; i < cell.size(); ++i)
    {
        if (cell[i].GetActive())
        {
            cell[i].Draw(window);
        }
    }
}

void Inventory::SetItemWindow()
{
    for (auto m : multiMap)
    {
        if (m.first == UiType::COMMON || m.first == UiType::ITEM || m.first == UiType::BUTTON || m.first == UiType::BOX || m.first == UiType::LINE)
        {
            m.second->SetActive(true);
        }
        else
        {
            m.second->SetActive(false);
        }
    }

    for (int i = 0; i < cell.size(); ++i)
    {
        if (!cell[i].GetActive())
        {
            cell[i].SetActive(true);
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            cell[(i * 12) + j].SetPosition(cellPos.x + (j * 80.f), cellPos.y + (i * 80.f));
        }
    }
    // ¾ÆÀÌÅÛµµ º¸ÀÌµµ·Ï Ãß°¡
    // Á¦ÀÛ, Ã¼ÀÎÁö¾À ÆÞ½º

    bag.SetPosition(bagPos.x, bagPos.y + 10.f);
    map.SetPosition(mapPos);
    make.SetPosition(makePos);
    changeScene.SetPosition(changeScenePos);
}

void Inventory::SetMapWindow()
{
    for (auto m : multiMap)
    {
        if (m.first == UiType::COMMON || m.first == UiType::MAP)
        {
            m.second->SetActive(true);
        }
        else
        {
            m.second->SetActive(false);
        }
    }

    for (int i = 0; i < cell.size(); ++i)
    {
        if (cell[i].GetActive())
        {
            cell[i].SetActive(false);
        }
    }

    xButton.SetPosition(mapImage.GetPosition() + sf::Vector2f{mapImage.sprite.getGlobalBounds().width / 2.f, - mapImage.sprite.getGlobalBounds().height / 2.f});
    //map.SetPosition(mapPos.x, mapPos.y + 10.f);
    //bag.SetPosition(bagPos);
    //make.SetPosition(makePos);
    //changeScene.SetPosition(changeScenePos);
}

void Inventory::SetMakeWindow()
{
    for (auto m : multiMap)
    {
        if (m.first == UiType::COMMON || m.first == UiType::MAKE || m.first == UiType::BUTTON || m.first == UiType::BOX || m.first == UiType::LINE)
        {
            m.second->SetActive(true);
        }
        else
        {
            m.second->SetActive(false);
        }
    }

    sf::Vector2f diff = { 0.f, invenLine.GetPosition().y - cell[0].GetPosition().y + 80.f };

    for (int i = 0; i < cell.size(); ++i)
    {
        if (!cell[i].GetActive())
        {
            cell[i].SetActive(true);
        }
        cell[i].SetPosition(cell[i].GetPosition() + diff);
    }

    make.SetPosition(makePos.x, makePos.y + 10.f);
    bag.SetPosition(bagPos);
    map.SetPosition(mapPos);
    changeScene.SetPosition(changeScenePos);
}

void Inventory::SetChangeSceneWindow()
{
    for (auto m : multiMap)
    {
        if (m.first == UiType::COMMON || m.first == UiType::CHANEGE || m.first == UiType::BUTTON || m.first == UiType::BOX)
        {
            m.second->SetActive(true);
        }
        else
        {
            m.second->SetActive(false);
        }
    }

    for (int i = 0; i < cell.size(); ++i)
    {
        if (cell[i].GetActive())
        {
            cell[i].SetActive(false);
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
    for (auto& m : multiMap)
    {
        m.second->SetActive(false);
    }

    for (int i = 0; i < cell.size(); ++i)
    {
        if (cell[i].GetActive())
        {
            cell[i].SetActive(false);
        }
    }
}

void Inventory::ButtonSetUp()
{
    bag.OnClick = [this]() {
        SetItemWindow();
    };
    map.OnClick = [this]() {
        SetMapWindow();
    };
    make.OnClick = [this]() {
        SetMakeWindow();
    };
    changeScene.OnClick = [this]() {
        SetChangeSceneWindow();
    };
    xButton.OnClick = [this]() {
        SetWindowClear();
    };
}
