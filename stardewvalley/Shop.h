#pragma once
#include"Item.h"
class Shop
{
private:
	std::vector<tagItemInfo>m_vItem;
	std::vector<tagItemInfo>::iterator m_viItem;


public:
	/*CShop();
	~CShop();*/

	void ItemSetup();
	int ItemOutput(const int num);

	tagItemInfo BuyItem(const int itemKind, const int num, int& gold);


	void AddItem(tagItemInfo item);

};

