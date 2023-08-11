#include "stdafx.h"
#include "Inventory.h"

Inventory::Inventory()
{
    tagItemInfo itemEmpty = { ITEM::ITEM_EMPTY ,"","",0,0,0 };

    equipTool = itemEmpty;
    equipSeed = itemEmpty;
    equipMake = itemEmpty;
    equipCrops = itemEmpty;
    equipMake = itemEmpty;
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
        std::cout << "아이템 번호  : " << ++itemCount << std::endl;
        std::cout << "이름  : " << i.name << std::endl;
        std::cout << "가격  : " << i.price << std::endl;
        std::cout << "능력치  : " << i.attribute << std::endl;
        std::cout << "설명  : " << i.description << std::endl;
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

tagItemInfo Inventory::SellItem(const int num, int& gold)
{
    tagItemInfo sellItem;

    itemI = item.begin() + (num - 1);
    sellItem = *itemI;
    item.erase(itemI);

    int sellPrice = sellItem.price / 2;

    std::cout << sellItem.name << "을" << sellPrice << "골드에 판매함" << std::endl;
    gold += sellPrice;

    return sellItem;
}

void Inventory::EquipItem(const int num)
{
    tagItemInfo beforeItem;
    
    itemI = item.begin() + (num - 1);

    switch (itemI->itemkind)
    {
    case ITEM::ITEM_TOOL:
        beforeItem = GetEquipArmor();
        SetEquipArmor(*m_viItem);
        m_vItem.erase(m_viItem);


        if (beforeItem.itemkind == ITEM::ITEM_ARMOR)
        {
            m_vItem.push_back(beforeItem);
        }
        break;
    case ITEM::ITEM_WEAPON:
        beforeItem = GetEquipWeapon();
        SetEquipWeapon(*m_viItem);
        m_vItem.erase(m_viItem);

        if (beforeItem.itemkind == ITEM::ITEM_WEAPON)
        {
            m_vItem.push_back(beforeItem);
        }
        break;
    }
}
