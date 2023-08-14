#include "stdafx.h"
#include "Inventory.h"
#include "InputMgr.h"
#include "DataTableMgr.h"
#include "StringTable.h"
#include "ResourceMgr.h"
#include "Player2.h"
#include "AllItemTable.h"
#include "Slot.h"

GameObject* Inventory::AddUi(UiType t, GameObject* go)
{
    if (!Exist(go))
    {
        invenUiObjects.push_back(std::make_pair(t, go));
    }
    return go;
}

bool Inventory::Exist(GameObject* go)
{
    for (auto& m : invenUiObjects)
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

    //for (int i = 0; i < 3; ++i)
    //{
    //    for (int j = 0; j < 12; ++j)
    //    {
    //        std::string num = std::to_string((i * 12) + j);
    //        cell.push_back((SpriteGo*)AddUi(UiType::LINE, new SpriteGo("graphics/MenuTiles.png", "invenCell" + num, "invenCell")));
    //        cell[(i * 12) + j]->SetOrigin(Origins::MC);
    //        cell[(i * 12) + j]->colliderOnOff = false;
    //    }
    //}

    //for (int i = 0; i < itemCapacity; ++i)
    //{
    //    std::string num = to_string(i);
    //    slot.push_back(Slot("graphics/MenuTiles.png", "invenCell" + num, "invenCell"));
    //    slot[i].slotIndex = i;
    //    slot[]
    //}

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            std::string num = std::to_string((i * 12) + j);
            slot.push_back(new Slot("graphics/MenuTiles.png", "invenCell" + num, "invenCell"));
            slot[(i * 12) + j]->SetOrigin(Origins::MC);
            slot[(i * 12) + j]->colliderOnOff = false;
            invenUiObjects.push_back({ UiType::LINE, dynamic_cast<GameObject*>(slot[(i * 12) + j])});
        }
    }

    AddUi(UiType::BOX, &invenBox);
    AddUi(UiType::LINE, &invenLine);
    AddUi(UiType::BUTTON, &bag);
    AddUi(UiType::BUTTON, &map);
    AddUi(UiType::BUTTON, &make);
    AddUi(UiType::BUTTON, &changeScene);
    AddUi(UiType::COMMON, &xButton);
    AddUi(UiType::MAP, &mapImage);
    AddUi(UiType::ITEM, &ring);
    AddUi(UiType::ITEM, &shoes);
    AddUi(UiType::ITEM, &hat);
    AddUi(UiType::ITEM, &charBg);
    AddUi(UiType::ITEM, &curFunds);
    AddUi(UiType::ITEM, &totalEarnings);
    AddUi(UiType::ITEM, &curFundsValue);
    AddUi(UiType::ITEM, &totalEarningsValue);
    AddUi(UiType::ITEM, &pl);
    AddUi(UiType::CHANEGE, &title);
    AddUi(UiType::CHANEGE, &end);
}

Inventory::~Inventory()
{
    for (auto it = invenUiObjects.begin(); it != invenUiObjects.end(); ++it)
    {
        delete it->second;
    }
    invenUiObjects.clear();
}

//void Inventory::AddPlayerItem(std::string name) // name = GameObject에 넘기는 이름이자 키
//{
//    auto Allitem = DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem)->table;
//
//    if (Allitem.find(name) != Allitem.end()) // 전체 아이템에 포함되어 있을 때
//    {
//        if (playerItemMap.find(name) == playerItemMap.end() && playerItemMap.size() < itemCapacity) // 플레이어 아이템에 없을 때
//        {
//            playerItemMap.insert(std::make_pair(name, Allitem.find(name)->second));
//            auto& tempPlIcon = playerItemMap.find(name)->second;
//            playerItemIcon.push_back((UiButton*)AddUi(UiType::TOOL, new UiButton(tempPlIcon.resource, tempPlIcon.name, tempPlIcon.nickName)));
//
//            GameObject* lastObject = nullptr;
//            auto range = invenUiObjects.equal_range(UiType::TOOL);
//            for (auto it = range.first; it != range.second; ++it)
//            {
//                lastObject = it->second;
//            }
//            if (lastObject) {
//                // 마지막 객체의 reset 함수 호출
//                lastObject->Reset();
//            }
//        }
//        else
//        {
//            playerItemMap.find(name)->second.count++;
//        }
//    }
//}

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

    playerItemList = player->GetPlayerItemList();
    curFundsInt = player->GetCurFundsInt(); // 현재 소지금
    totalEarningsInt = player->GetTotalEarningsInt(); // 총합 자금

    for (auto i : invenUiObjects)
    {
        i.second->Init();
    }
}

void Inventory::Reset()
{
    for (auto m : invenUiObjects)
    {
        m.second->Reset();
    }

    // 오브젝트 초기 세팅
    {
        invenBox.SetSize({ 1040.f, 670.f });
        invenBox.SetOrigin(Origins::MC);
        invenBox.SetPosition(position);

        cellPos = { invenBox.vertexArray[0].position.x + 80.f, invenBox.vertexArray[0].position.y + 100.f };
        //for (int i = 0; i < 3; ++i)
        //{
        //    for (int j = 0; j < 12; ++j)
        //    {
        //        cell[(i * 12) + j]->SetPosition(cellPos.x + (j * 80.f), cellPos.y + (i * 80.f));
        //    }
        //}

        invenLine.SetSize(1040.f);
        invenLine.SetOrigin(Origins::MC);
        //invenLine.SetPosition(position.x, cell[35]->GetPosition().y + 80.f);

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
        //ring.SetPosition(cell[0]->GetPosition().x, invenLine.GetPosition().y + 80.f);
        ring.colliderOnOff = false;
        shoes.SetOrigin(Origins::MC);
        //shoes.SetPosition(cell[0]->GetPosition().x, ring.GetPosition().y + 80.f);
        shoes.colliderOnOff = false;
        hat.SetOrigin(Origins::MC);
        //hat.SetPosition(cell[0]->GetPosition().x, shoes.GetPosition().y + 80.f);
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
        title.text.setFont(*RESOURCE_MGR.GetFont("fonts/SDMiSaeng.ttf"));
        title.text.setString(stringTable1->Get("TOTITLE"));
        title.text.setCharacterSize(100);
        title.text.setFillColor(sf::Color::Black);
        title.SetPosition(position.x, position.y - 80.f);
        title.text.setPosition(title.GetPosition().x, title.GetPosition().y - 40.f);
        title.SetScale(1.5f, 1.5f);
        title.SetOrigin(Origins::MC);
        std::cout << title.text.getPosition().x << "," << title.text.getPosition().y << std::endl;
        std::cout << title.sprite.getPosition().x << "," << title.sprite.getPosition().y << std::endl;
        end.text.setFont(*RESOURCE_MGR.GetFont("fonts/SDMiSaeng.ttf"));
        end.text.setString(stringTable1->Get("END"));
        end.text.setCharacterSize(100);
        end.text.setFillColor(sf::Color::Black);
        end.SetPosition(title.GetPosition().x,title.GetPosition().y + title.sprite.getGlobalBounds().height + 30.f);
        end.text.setPosition(end.GetPosition().x, end.GetPosition().y - 40.f);
        end.SetScale(1.5f, 1.5f);
        end.SetOrigin(Origins::MC);

        player->GetAnimation().Play("Idle");
        pl.sprite = player->sprite;
        pl.SetOrigin(Origins::MC);
        pl.SetPosition(charBg.GetPosition());

        //AddPlayerItem("pick");
        //AddPlayerItem("ax");
        //AddPlayerItem("homi");
        //AddPlayerItem("waterCan");
        //AddPlayerItem("hook");

    }

    SetWindowClear();
    ButtonSetUp();
}

void Inventory::Release()
{
}

void Inventory::Update(float dt)
{
    for (auto m : invenUiObjects)
    {
        m.second->Update(dt);
    }

    if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
    {
        if (!invenOnOff)
        {
            SetItemWindow();
            invenOnOff = true;
        }
        else
        {
            invenOnOff = false;
            SetWindowClear();
        }
    }
}

void Inventory::Draw(sf::RenderWindow& window)
{
    for (auto m : invenUiObjects)
    {
        if (m.second->GetActive())
        {
            m.second->Draw(window);
        }
    }
}

void Inventory::SetItemWindow()
{
    for (auto m : invenUiObjects)
    {
        if (m.first == UiType::COMMON || m.first == UiType::ITEM || m.first == UiType::BUTTON || m.first == UiType::BOX || m.first == UiType::LINE || m.first == UiType::TOOL)
        {
            m.second->SetActive(true);
        }
        else
        {
            m.second->SetActive(false);
        }
    }

    //for (int i = 0; i < 3; ++i)
    //{
    //    for (int j = 0; j < 12; ++j)
    //    {
    //        cell[(i * 12) + j]->SetPosition(cellPos.x + (j * 80.f), cellPos.y + (i * 80.f));
    //    }
    //}
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
        if (m.first == UiType::COMMON || m.first == UiType::MAP)
        {
            m.second->SetActive(true);
        }
        else
        {
            m.second->SetActive(false);
        }
    }

    xButton.SetPosition(mapImage.GetPosition() + sf::Vector2f{mapImage.sprite.getGlobalBounds().width / 2.f, - mapImage.sprite.getGlobalBounds().height / 2.f});
}

void Inventory::SetMakeWindow()
{
    for (auto m : invenUiObjects)
    {
        if (m.first == UiType::COMMON || m.first == UiType::MAKE || m.first == UiType::BUTTON || m.first == UiType::BOX || m.first == UiType::LINE || m.first == UiType::TOOL)
        {
            m.second->SetActive(true);
        }
        else
        {
            m.second->SetActive(false);
        }
    }

    //sf::Vector2f diff = { 0.f, invenLine.GetPosition().y - cell[0]->GetPosition().y + 80.f };

    //for (int i = 0; i < cell.size(); ++i)
    //{
    //    cell[i]->SetPosition(cell[i]->GetPosition() + diff);
    //}

    make.SetPosition(makePos.x, makePos.y + 10.f);
    bag.SetPosition(bagPos);
    map.SetPosition(mapPos);
    changeScene.SetPosition(changeScenePos);
}

void Inventory::SetChangeSceneWindow()
{
    for (auto m : invenUiObjects)
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
        m.second->SetActive(false);
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

void Inventory::SetPlayer(Player2* p)
{
    player = p;
}
