#include "stdafx.h"
#include "SaveLoadData.h"
#include "Player2.h"
#include "rapidcsv.h"
#include "Stone.h"
#include "Timber.h"
#include "Weed.h"
#include "Tree.h"
#include "HoeDirt.h"

SaveLoadData::~SaveLoadData()
{
}

void SaveLoadData::SaveCSV(DataLoad* sdata)
{
	// PLAYER DATA SAVE
	{
		const std::string fileName1 = "tables/save_playerItemList.csv";
		rapidcsv::Document pl_doc(fileName1);
		pl_doc.Clear();

		pl_doc.SetColumnName(0,"ItemId");
		pl_doc.SetColumnName(1,"Count");
		pl_doc.SetColumnName(2,"Index");

		std::vector<int> itemId;
		std::vector<int> count;
		std::vector<int> index;

		for (auto i : sdata->pl_ItemList)
		{
			itemId.push_back((int)i.itemId);
			count.push_back(i.count);
			index.push_back(i.index);
		}

		pl_doc.SetColumn("ItemId", itemId);
		pl_doc.SetColumn("Count", count);
		pl_doc.SetColumn("Index", index);

		pl_doc.Save();
	}

	// SINGLE DATA SAVE
	{
		const std::string fileName2 = "tables/save_singleData.csv";
		rapidcsv::Document single_doc(fileName2);
		single_doc.Clear();

		single_doc.SetColumnName(0,"totalEarningsInt");
		single_doc.SetColumnName(1,"money");
		single_doc.SetColumnName(2,"energy");
		single_doc.SetColumnName(3,"min");
		single_doc.SetColumnName(4,"hour");
		single_doc.SetColumnName(5,"day");

		std::vector<int> values = { sdata->pl_totalMoney, sdata->pl_money, sdata->pl_energy, sdata->game_min, sdata->game_hour, sdata->game_day };
		single_doc.SetCell<int>("totalEarningsInt", 0, sdata->pl_totalMoney);
		single_doc.SetCell<int>("money", 0, sdata->pl_money);
		single_doc.SetCell<int>("energy", 0, sdata->pl_energy);
		single_doc.SetCell<int>("min", 0, sdata->game_min);
		single_doc.SetCell<int>("hour", 0, sdata->game_hour);
		single_doc.SetCell<int>("day", 0, sdata->game_day);

		single_doc.Save();
	}

	// MAP OBJ DATA SAVE
	{
		std::ofstream outputFile("tables/save_mapObj.csv");
		outputFile.clear();

		if (!outputFile.is_open())
		{
			cout << "ERR: 파일을 열 수 없습니다." << endl;
		}

		outputFile << "cols,rows" << endl;
		outputFile << cols << "," << rows << endl;

		outputFile << "index,indexX,indexY,left,top,width,height,type" << endl;
		for (int i = 0; i < sdata->stones.size(); ++i)
		{
			outputFile << i << "," << sdata->stones[i]->GetIndex().x << "," << sdata->stones[i]->GetIndex().y << "," << sdata->stones[i]->GetTexRect().left << "," << sdata->stones[i]->GetTexRect().top << "," <<
				sdata->stones[i]->GetTexRect().width << "," << sdata->stones[i]->GetTexRect().height << "," << (int)ObjType::Stone << endl;
		}
		for (int i = 0; i < sdata->weeds.size(); ++i)
		{
			outputFile << i + sdata->stones.size() << "," << sdata->weeds[i]->GetIndex().x << "," << sdata->weeds[i]->GetIndex().y << "," << sdata->weeds[i]->GetTexRect().left << "," << sdata->weeds[i]->GetTexRect().top << "," <<
				sdata->weeds[i]->GetTexRect().width << "," << sdata->weeds[i]->GetTexRect().height << "," << (int)ObjType::Weed << endl;
		}
		for (int i = 0; i < sdata->timbers.size(); ++i)
		{
			outputFile << i + sdata->weeds.size() + +sdata->stones.size() << "," << sdata->timbers[i]->GetIndex().x << "," << sdata->timbers[i]->GetIndex().y << "," << sdata->timbers[i]->GetTexRect().left << "," << sdata->timbers[i]->GetTexRect().top << "," <<
				sdata->timbers[i]->GetTexRect().width << "," << sdata->timbers[i]->GetTexRect().height << "," << (int)ObjType::Timber << endl;
		}
		for (int i = 0; i < sdata->trees.size(); ++i)
		{
			outputFile << i + sdata->weeds.size() + +sdata->stones.size() + sdata->timbers.size() << "," << sdata->trees[i]->stump->GetIndex().x << "," << sdata->trees[i]->stump->GetIndex().y << "," << sdata->trees[i]->stump->GetTexRect().left << "," << sdata->trees[i]->stump->GetTexRect().top << "," <<
				sdata->trees[i]->stump->GetTexRect().width << "," << sdata->trees[i]->stump->GetTexRect().height << "," << (int)ObjType::Tree << endl;
		}
		outputFile.close();
	}
}

void SaveLoadData::LoadCSV(DataLoad* sdata)
{	
	// PLAYER DATA LOAD
	{
		const std::string fileName1 = "tables/save_playerItemList.csv";
		rapidcsv::Document pl_doc(fileName1);

		std::vector<ItemId>id;
		std::vector<int>count;
		std::vector<int>index;
		for (auto i : pl_doc.GetColumn<int>("ItemId"))
		{
			id.push_back(static_cast<ItemId>(i));
		}
		count = pl_doc.GetColumn<int>("Count");
		index = pl_doc.GetColumn<int>("Index");
		sdata->pl_ItemList.clear();
		for (int i = 0; i < id.size(); ++i)
		{
			sdata->pl_ItemList.push_back({ id[i], count[i], index[i] });
		}
	}

	// SINGLE DATA LOAD
	{
		const std::string fileName2 = "tables/save_singleData.csv";
		rapidcsv::Document single_doc(fileName2);

		std::vector<int>values;
		values = single_doc.GetRow<int>(0);
		sdata->pl_totalMoney = values[0];
		sdata->pl_money = values[1];
		sdata->pl_energy = values[2];
		sdata->game_min = values[3];
		sdata->game_hour = values[4];
		sdata->game_day = values[5];
	}

	// MAP OBJ DATA LOAD
	{
		const std::string fileName3 = "tables/save_mapObj.csv";
		rapidcsv::Document mapObj_doc(fileName3);
		table.clear();

		for (int i = 2; i < mapObj_doc.GetRowCount(); i++)
		{
			auto rows = mapObj_doc.GetRow<int>(i);
			ObjectInfo oInfo
			{
				rows[1], rows[2], (float)rows[3], (float)rows[4], (float)rows[5], (float)rows[6], (ObjType)rows[7]
			};
			table.insert({ rows[0], oInfo });
		}
	}
	
	// LOAD WITH CHANGES : stone, timber, weed, tree LEFT
	{
		if (sdata->game_hour >= 24)
		{
			sdata->pl_energy = sdata->pl_energy - (sdata->pl_energy * (((sdata->game_hour - 24) * 60 + sdata->game_min)/10) * 0.025f);
		}
		sdata->pl_energy = 270;
		sdata->game_hour = 6;
		sdata->game_min = 0;
		sdata->game_day++;
	}
}