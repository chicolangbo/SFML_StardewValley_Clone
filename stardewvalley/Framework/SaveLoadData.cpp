#include "stdafx.h"
#include "SaveLoadData.h"
#include "Player2.h"
#include "rapidcsv.h"

SaveLoadData::~SaveLoadData()
{
}

void SaveLoadData::SaveData(DataLoad* sdata)
{
	playerItemList = sdata->pl_ItemList;
	totalEarningsInt = sdata->pl_totalMoney;
	money = sdata->pl_money;
	energy = sdata->pl_energy;
	min = sdata->game_min;
	hour = sdata->game_hour;
	day = sdata->game_day;
}

void SaveLoadData::SaveCSV()
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

		for (auto i : playerItemList)
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

		std::vector<int> values = { totalEarningsInt, money, energy, min, hour, day };
		single_doc.SetCell<int>("totalEarningsInt", 0, totalEarningsInt);
		single_doc.SetCell<int>("money", 0, money);
		single_doc.SetCell<int>("energy", 0, energy);
		single_doc.SetCell<int>("min", 0, min);
		single_doc.SetCell<int>("hour", 0, hour);
		single_doc.SetCell<int>("day", 0, day);

		single_doc.Save();
	}
}

void SaveLoadData::LoadCSV(DataLoad* ldata)
{
	// TEST SAVE VALUE
	//playerItemList.push_back({ ItemId::branch, 1, 5 });
	//totalEarningsInt = 30;
	//money = 50;
	//energy = 200;
	//day = 2;
	//hour = 25;
	//min = 30; // 60 + 30 = 90 => 2.5*9 = 22.5 => 270 - 22.5 = 248.5
	
	// 저장된 파일 데이터 읽어오기
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

		for (int i = 0; i < id.size(); ++i)
		{
			playerItemList.push_back({ id[i], count[i], index[i] });
		}
	}

	// SINGLE DATA LOAD
	{
		const std::string fileName2 = "tables/save_singleData.csv";
		rapidcsv::Document single_doc(fileName2);

		std::vector<int>values;
		values = single_doc.GetRow<int>(0);
		totalEarningsInt = values[0];
		money = values[1];
		energy = values[2];
		min = values[3];
		hour = values[4];
		day = values[5];
	}

	// LOAD WITH NO CHANGE
	{
		ldata->pl_ItemList = playerItemList;
		ldata->pl_money = money;
		ldata->pl_totalMoney = totalEarningsInt;
	}
	
	// LOAD WITH CHANGES : stone, timber, weed, tree LEFT
	{
		if (hour >= 24)
		{
			ldata->pl_energy =  energy - (energy * (((hour - 24) * 60 + min)/10) * 0.025f);
		}
		ldata->pl_energy = 270;
		ldata->game_hour = 6;
		ldata->game_min = 0;
		ldata->game_day++;
	}
}