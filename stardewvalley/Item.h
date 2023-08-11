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
	ITEM itemkind;
	std::string name;
	std::string description;
	int attribute;
	int price;
	int count;

	tagItemInfo& operator=(const tagItemInfo& other)
	{
		attribute = other.attribute;
		count = other.count;
		description = other.description;
		itemkind = other.itemkind;
		name = other.name;
		price = other.price;
		return *this;
	}
};











