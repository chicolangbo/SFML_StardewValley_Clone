#pragma once
#include<iostream>
#include<vector>
#include<string>

enum class ITEM
{
	ITEM_EMPTY,
	ITEM_TOOL,
	ITEM_MAKE,
	ITEM_RESOURCE,
	ITEM_SEED,
	ITEM_CROPS,
	ITEM_SOLDOUT
};

struct tagItemInfo
{
	ItemId itemId = ItemId::none;
	int count = 0;//°¹¼ö
	int index = 0;//À§Ä¡

	tagItemInfo& operator=(const tagItemInfo& other)
	{
		count = other.count;
		itemId = other.itemId;
		index = other.index;
		return *this;
	}
};











