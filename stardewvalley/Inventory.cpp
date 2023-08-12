#include "stdafx.h"
#include "Inventory.h"

GameObject* Inventory::AddUi(GameObject* go)
{
    if (!Exist(go))
    {
        uiObjects.push_back(go);
    }
    return go;
}

bool Inventory::Exist(GameObject* go)
{
    return std::find(uiObjects.begin(), uiObjects.end(), go) != uiObjects.end();
}

Inventory::Inventory(const std::string& n)
    : GameObject(n), invenBox("graphics/box1.png", "invenBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE), 
    invenLine("graphics/invenBoxLine.png", "invenBoxLine", { 24,0,52,27 }, { 0,0,100,27 }, THREE_SLICE),
    bag("graphics/Cursors.ko-KR.png", "invenBag", "invenBag"), 
    map("graphics/Cursors.ko-KR.png", "invenMap", "invenMap"), 
    make("graphics/Cursors.ko-KR.png", "invenMake", "invenMake"), 
    changeScene("graphics/Cursors.ko-KR.png", "invenSetting", "invenSetting")
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
    tagItemInfo pick = { ITEM::ITEM_TOOL, "���", "���", 0, 0, 1 };
    tagItemInfo ax = { ITEM::ITEM_TOOL, "����", "����", 0, 0, 1 };
    tagItemInfo homi = { ITEM::ITEM_TOOL, "���", "���", 0, 0, 1 };
    tagItemInfo waterCan = { ITEM::ITEM_TOOL, "���Ѹ���", "���Ѹ���", 0, 0, 1 };
    tagItemInfo hook = { ITEM::ITEM_TOOL, "��", "��", 0, 0, 1 };
    addItem(pick);
    addItem(ax);
    addItem(homi);
    addItem(waterCan);
    addItem(hook);

    
    AddUi(&invenBox);
    AddUi(&invenLine);
    AddUi(&bag);
    AddUi(&map);
    AddUi(&make);
    AddUi(&changeScene);
}

Inventory::~Inventory()
{
}

int Inventory::ShowInventory()
{
    int itemCount = 0;


    for (auto& i : item)
    {
        std::cout << "==========================" << std::endl;
        std::cout << "������ ��ȣ  : " << ++itemCount << std::endl;
        std::cout << "�̸�  : " << i.name << std::endl;
        std::cout << "����  : " << i.price << std::endl;
        std::cout << "�ɷ�ġ  : " << i.attribute << std::endl;
        std::cout << "����  : " << i.description << std::endl;
        std::cout << "==========================" << std::endl;
    }

    return itemCount;
}

void Inventory::addItem(tagItemInfo item)
{
    if (item.itemkind != ITEM::ITEM_EMPTY)
    {
        this->item.push_back(item);
    }
}

//tagItemInfo Inventory::SellItem(const int num, int& gold)
//{
//    tagItemInfo sellItem;
//
//    itemI = item.begin() + (num - 1);
//    sellItem = *itemI;
//    item.erase(itemI);
//
//    int sellPrice = sellItem.price / 2;
//
//    std::cout << sellItem.name << "��" << sellPrice << "��忡 �Ǹ���" << std::endl;
//    gold += sellPrice;
//
//    return sellItem;
//}
//
//void Inventory::EquipItem(const int num)
//{
//    tagItemInfo beforeItem;
//    
//    itemI = item.begin() + (num - 1);
//
//    switch (itemI->itemkind)
//    {
//    case ITEM::ITEM_TOOL:
//        beforeItem = GetEquipArmor();
//        SetEquipArmor(*m_viItem);
//        m_vItem.erase(m_viItem);
//
//
//        if (beforeItem.itemkind == ITEM::ITEM_ARMOR)
//        {
//            m_vItem.push_back(beforeItem);
//        }
//        break;
//    case ITEM::ITEM_WEAPON:
//        beforeItem = GetEquipWeapon();
//        SetEquipWeapon(*m_viItem);
//        m_vItem.erase(m_viItem);
//
//        if (beforeItem.itemkind == ITEM::ITEM_WEAPON)
//        {
//            m_vItem.push_back(beforeItem);
//        }
//        break;
//    }
//}

void Inventory::Init()
{
    ////ó�� Ŭ��
    //tagItemInfo onMouseItem;
    //onMouseItem = item[0];
    //item[0] = empty;

    ////����� �ٽ� Ŭ��
    //item[3] = onMouseItem;
    //onMouseItem = empty;

    ////�̹� �ִ� ���� Ŭ��
    //tagItemInfo tempItem;
    //tempItem = item[3];

    //item[3] = onMouseItem;
    //onMouseItem = tempItem;

    for (auto go : uiObjects)
    {
        if (go->GetActive())
        {
            go->Init();
        }
    }

    for (int i = 0; i < cell.size(); ++i)
    {
        cell[i].Init();
    }
}

void Inventory::Reset()
{
    for (auto go : uiObjects)
    {
        if (go->GetActive())
        {
            go->Reset();
        }
    }
    for (int i = 0; i < cell.size(); ++i)
    {
        cell[i].Reset();
    }

    invenBox.SetSize({ 1040.f, 800.f });
    invenBox.SetOrigin(Origins::MC);
    invenBox.SetPosition(position);

    sf::Vector2f initPosition = { invenBox.vertexArray[0].position.x + 80.f, invenBox.vertexArray[0].position.y + 100.f };
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            cell[(i * 12) + j].SetPosition(initPosition.x + (j * 80.f), initPosition.y + (i * 80.f));
        }
    }

    invenLine.SetSize(1040.f);
    invenLine.SetOrigin(Origins::MC);
    invenLine.SetPosition(position.x, cell[35].GetPosition().y + 80.f);
}

void Inventory::Update(float dt)
{
    for (auto go : uiObjects)
    {
        if (go->GetActive())
        {
            go->Update(dt);
        }
    }
}

void Inventory::Draw(sf::RenderWindow& window)
{
    for (auto go : uiObjects)
    {
        if (go->GetActive())
        {
            go->Draw(window);
        }
    }

    for (int i = 0; i < cell.size(); ++i)
    {
        cell[i].Draw(window);
    }
}
