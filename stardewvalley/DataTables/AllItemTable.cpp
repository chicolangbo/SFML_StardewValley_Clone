#include "stdafx.h"
#include "AllItemTable.h"
#include "rapidcsv.h"

bool AllItemTable::Load()
{
	std::string filename = "tables/AllItem.csv";

	rapidcsv::Document doc(filename);

	std::vector<int> itemId = doc.GetColumn<int>(0);
	std::vector<int> itemType = doc.GetColumn<int>(1);
	std::vector<std::string> name_e = doc.GetColumn<std::string>(2);
	std::vector<std::string> name_k = doc.GetColumn<std::string>(3);
	std::vector<std::string> nickName = doc.GetColumn<std::string>(4);
	std::vector<std::string> resourceId = doc.GetColumn<std::string>(5);
	std::vector<std::string> description_e = doc.GetColumn<std::string>(6);
	std::vector<std::string> description_k = doc.GetColumn<std::string>(7);
	std::vector<int> price = doc.GetColumn<int>(8);

	for (int i = 0; i < itemType.size(); ++i)
	{
		ItemInfo values;
		values.itemId = (ItemId)itemId[i];
		values.itemkind = (ITEM)itemType[i];
		values.name_e = name_e[i];
		values.name_k = name_k[i];
		values.nickName = nickName[i];
		values.description_e = description_e[i];
		values.description_k = description_k[i];
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

const std::wstring AllItemTable::GetUniName(ItemId id) // Kor
{
	string multibyteString = Get(id)->name_k;
	return multibyte_to_uni(multibyteString);
}

const std::wstring AllItemTable::GetUniDescription(ItemId id)
{
	string multibyteString = Get(id)->description_k;
	return multibyte_to_uni(multibyteString);
}

wstring AllItemTable::multibyte_to_uni(const std::string& str)
{
	int nLen = str.size();
	wchar_t warr[256];
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), -1, warr, nLen);

	return warr;
}
