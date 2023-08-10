#include "stdafx.h"
#include "WallTable.h"
#include "rapidcsv.h"

bool WallTable::Load()
{
	std::string filename = "tables/Wall.csv";

	rapidcsv::Document doc(filename);

	std::vector<int> wallType = doc.GetColumn<int>(0);
	std::vector<float> left = doc.GetColumn<float>(1);
	std::vector<float> top = doc.GetColumn<float>(2);
	std::vector<float> width = doc.GetColumn<float>(3);
	std::vector<float> height = doc.GetColumn<float>(4);

	for (int i = 0; i < wallType.size(); ++i)
	{
		WallInfo values;
		values.wallType = (Wall::Types)wallType[i];
		values.left = left[i];
		values.top = top[i];
		values.width = width[i];
		values.height = height[i];
		table.insert({ (Wall::Types)wallType[i], values });
	}
	// ±è¹ÎÁö, 230809, Ãß°¡
	size = wallType.size();
	//
	return true;
}

void WallTable::Release()
{
	table.clear();
}

const WallInfo& WallTable::Get(Wall::Types t)
{
	auto find = table.find(t);
	return find->second;
}
