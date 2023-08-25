#pragma once
#include "Item.h"
#include "Singleton.h"
#include "SceneGame.h"
#include "ObjectTable.h"
#include "Crop.h"

//struct CropLoadData
//{
//	int type;
//	int x;
//	int y;
//	int date;
//	int day;
//	int level;
//	int curday;
//	int water;
//	int sortl;
//	int sorto;
//};

class Stone;
class Timber;
class Weed;
class Tree;

class SaveLoadData : public Singleton<SaveLoadData>
{
	friend Singleton<SaveLoadData>;

protected:
	int cols = 38;
	int rows = 41;

public:
	unordered_map<int, ObjectInfo> table;
	std::vector<CropLoadData> parsnip;
	std::vector<CropLoadData> potato;
	std::vector<CropLoadData> cauliflower;

	SaveLoadData() = default;
	virtual ~SaveLoadData() override;

	void SaveCSV(DataLoad* sdata);
	void LoadCSV(DataLoad* ldata);

	template <typename T>
	void SaveCrops(std::list<T>& pool, std::vector<int>& type, std::vector<int>& x, std::vector<int>& y, std::vector<int>& date, std::vector<int>& day, std::vector<int>& level, std::vector<int>& curday, std::vector<int>& water, std::vector<int>& sortl, std::vector<int>& sorto)
	{
		for (auto i : pool)
		{
			CropSaveData parsnip = i->GetLoadData();
			type.push_back((int)parsnip.id);
			x.push_back(parsnip.index.x);
			y.push_back(parsnip.index.y);
			date.push_back(parsnip.date);
			day.push_back(parsnip.day);
			level.push_back(parsnip.level);
			curday.push_back(parsnip.currentday);
			water.push_back(parsnip.isWatered);
			sortl.push_back(parsnip.sortLayer);
			sorto.push_back(parsnip.sortOrder);
		}
	}
};

#define SAVELOAD_DATA (SaveLoadData::Instance())