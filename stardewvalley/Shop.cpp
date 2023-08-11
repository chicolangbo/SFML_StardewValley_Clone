#include "stdafx.h"
#include "Shop.h"

void Shop::ItemSetup()
{
	tagItemInfo armor1;
	armor1.itemkind = ITEM::ITEM_ARMOR;
	armor1.name = "청바지";
	armor1.price = 50;
	armor1.attribute = 10;
	armor1.description = "시장에서 산 청바지";
	armor1.count = 1;
	m_vItem.push_back(armor1);

	tagItemInfo armor2;
	armor2.itemkind = ITEM::ITEM_ARMOR;
	armor2.name = "패딩자켓";
	armor2.price = 150;
	armor2.attribute = 210;
	armor2.description = "등골브레이커";
	armor2.count = 1;
	m_vItem.push_back(armor2);


	tagItemInfo weapon1;
	weapon1.itemkind = ITEM::ITEM_WEAPON;
	weapon1.name = "집행검";
	weapon1.price = 1500;
	weapon1.attribute = 10;
	weapon1.description = "리니지에 나오는 전설의 검";
	weapon1.count = 1;
	m_vItem.push_back(weapon1);

	tagItemInfo weapon2;
	weapon2.itemkind = ITEM::ITEM_WEAPON;
	weapon2.name = "광선검";
	weapon2.price = 500;
	weapon2.attribute = 30;
	weapon2.description = "스타워즈에 등장함";
	weapon2.count = 1;
	m_vItem.push_back(weapon2);
}

int Shop::ItemOutput(const int num)
{
	int itemCount = 0;
	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem)
	{

		if (m_viItem->itemkind != (ITEM)num)continue;
		std::cout << "========================" << std::endl;
		std::cout << "아이템 번호 : " << ++itemCount << std::endl;
		std::cout << "이름 : " << m_viItem->name << std::endl;
		std::cout << "가격 : " << m_viItem->price << std::endl;
		std::cout << "능력치 : " << m_viItem->attribute<< std::endl;
		std::cout << "설명 : " << m_viItem->description << std::endl;
		std::cout << "갯수 : ";
		(m_viItem->count > 0) ? std::cout << m_viItem->count << std::endl : std::cout << "매진" << std::endl;
		std::cout << "========================" << std::endl;

	}
	return itemCount;
}

tagItemInfo Shop::BuyItem(const int itemKind, const int num, int& gold)
{
	tagItemInfo buyItem;
	buyItem.itemkind = ITEM::ITEM_EMPTY;
	int itemCount = 0;
	m_viItem = m_vItem.begin();

	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem)
	{
		if (m_viItem->itemkind != (ITEM)itemKind)continue;

		if (++itemCount == num)
		{
			if (gold >= m_viItem->price)
			{
				if (m_viItem->count > 0)
				{
					std::cout << m_viItem->name << "을" << m_viItem->price << "gold에 구매함" << std::endl;
					gold -= m_viItem->price;
					m_viItem->count--;
					buyItem = *m_viItem;
				}
				else
				{
					std::cout << "없어~" << std::endl;
				}
			}
			else
			{
				std::cout << "돈없음!!!" << std::endl;
			}
			break;
		}
	}
	return buyItem;
}

void Shop::AddItem(tagItemInfo item)
{
	bool isNemItem = true;
	m_viItem = m_vItem.begin();

	for (m_viItem; m_viItem != m_vItem.end(); ++m_viItem)
	{
		if (m_viItem->itemkind != item.itemkind)continue;

		if (m_viItem->name.compare(item.name) == 0) {
			m_viItem->count++;
			isNemItem = false;
			break;
		}
	}
	if (isNemItem == true)
	{
		m_vItem.push_back(item);
	}

}
