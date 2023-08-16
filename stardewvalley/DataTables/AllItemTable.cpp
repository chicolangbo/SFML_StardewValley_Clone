#include "stdafx.h"
#include "AllItemTable.h"
#include "rapidcsv.h"

bool AllItemTable::Load()
{
	std::string filename = "tables/AllItem.csv";

	rapidcsv::Document doc(filename);

	std::vector<int> itemId = doc.GetColumn<int>(0);
	std::vector<int> itemType = doc.GetColumn<int>(1);
	std::vector<std::string> name = doc.GetColumn<std::string>(2);
	std::vector<std::string> nickName = doc.GetColumn<std::string>(3);
	std::vector<std::string> resourceId = doc.GetColumn<std::string>(4);
	std::vector<std::string> description = doc.GetColumn<std::string>(5);
	std::vector<int> price = doc.GetColumn<int>(6);

	for (int i = 0; i < itemType.size(); ++i)
	{
		ItemInfo values;
		values.itemId = (ItemId)itemId[i];
		values.itemkind = (ITEM)itemType[i];
		values.name = name[i];
		values.nickName = nickName[i];
		values.description = description[i];
		values.resource = resourceId[i];
		values.price = price[i];
		table.insert({ (ItemId)itemId[i], values});
	}
	size = itemType.size();
	return true;
}

void AllItemTable::Release()
{
	table.clear();
}

const ItemInfo* AllItemTable::Get(ItemId id)
{
	auto find = table.find(id);
	if (find != table.end())
	{
		return &find->second;
	}
	else
	{
		return nullptr;
	}
}
