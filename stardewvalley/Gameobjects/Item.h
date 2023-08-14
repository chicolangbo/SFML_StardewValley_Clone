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
	//ITEM itemkind;
	std::string name;
	//std::string nickName = "";
	//std::string description;
	//std::string resource;
	//int price;
	int count;
	int index;

	tagItemInfo& operator=(const tagItemInfo& other)
	{
		count = other.count;
		//description = other.description;
		//itemkind = other.itemkind;
		name = other.name;
		//nickName = other.nickName;
		//price = other.price;
		//resource = other.resource;
		return *this;
	}
};











