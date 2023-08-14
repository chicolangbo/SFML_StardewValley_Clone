#include "stdafx.h"
#include "AllItemTable.h"
#include "rapidcsv.h"

bool AllItemTable::Load()
{
	std::string filename = "tables/AllItem.csv";

	rapidcsv::Document doc(filename);

	std::vector<int> itemType = doc.GetColumn<int>(0);
	std::vector<std::string> name = doc.GetColumn<std::string>(1);
	std::vector<std::string> nickName = doc.GetColumn<std::string>(2);
	std::vector<std::string> resourceId = doc.GetColumn<std::string>(3);
	std::vector<std::string> description = doc.GetColumn<std::string>(4);
	std::vector<int> price = doc.GetColumn<int>(5);

	for (int i = 0; i < itemType.size(); ++i)
	{
		AllItemInfo values;
		values.itemkind = (ITEM)itemType[i];
		values.name = name[i];
		values.nickName = nickName[i];
		values.description = description[i];
		values.resource = resourceId[i];
		values.price = price[i];
		table.insert({ name[i], values});
	}
	size = itemType.size();
	return true;
}

void AllItemTable::Release()
{
	table.clear();
}

const AllItemInfo* AllItemTable::Get(std::string name)
{
	auto find = table.find(name);
	if (find != table.end())
	{
		return &find->second;
	}
	else
	{
		return nullptr;
	}
}
