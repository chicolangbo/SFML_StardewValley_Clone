#include "stdafx.h"
#include "Inventory.h"

Inventory::Inventory(const std::string& n)
    : GameObject(n), invenBox("graphics/box1.png", "invenBox", { 22,27,36,37 }, { 0,0,80,80 }, NINE_SLICE), 
    invenBoxLine("graphics/invenBoxLine.png", "invenBoxLine", { 24,0,52,27 }, { 0,0,100,27 }, THREE_SLICE),
    bag("graphics/Cursors.ko-KR.png", "invenBag", "invenBag"), 
    map("graphics/Cursors.ko-KR.png", "invenMap", "invenMap"), 
    make("graphics/Cursors.ko-KR.png", "invenMake", "invenMake"), 
    changeScene("graphics/Cursors.ko-KR.png", "invenSetting", "invenSetting")
{

    sf::Vector2f initPosition = { 0.f, 0.f };
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            SpriteGo tempCell = SpriteGo("graphics/MenuTiles.png", "invenCell", "invenCell");
            cell.push_back(tempCell);
            cell[i].SetPosition(initPosition.x + (j*60.f), initPosition.y + (i*60.f));
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
        std::cout << "¾ÆÀÌÅÛ ¹øÈ£  : " << ++itemCount << std::endl;
        std::cout << "ÀÌ¸§  : " << i.name << std::endl;
        std::cout << "°¡°Ý  : " << i.price << std::endl;
        std::cout << "´É·ÂÄ¡  : " << i.attribute << std::endl;
        std::cout << "¼³¸í  : " << i.description << std::endl;
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
//    std::cout << sellItem.name << "À»" << sellPrice << "°ñµå¿¡ ÆÇ¸ÅÇÔ" << std::endl;
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
}

void Inventory::Reset()
{
}

void Inventory::Update(float dt)
{
}

void Inventory::Draw(sf::RenderWindow& window)
{
    bag.SetPosition(0, 0);
    bag.Draw(window);
    map.Draw(window);
    make.Draw(window);
    changeScene.Draw(window);
    invenBox.Draw(window);
    invenBoxLine.Draw(window);
}
