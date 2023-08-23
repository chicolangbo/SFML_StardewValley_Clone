#pragma once
#include "Item.h"
#include "Singleton.h"
#include "SceneGame.h"

class Stone;
class Timber;
class Weed;
class Tree;

class SaveLoadData : public Singleton<SaveLoadData>
{
	friend Singleton<SaveLoadData>;

protected:
	// PLAYER
	std::list<tagItemInfo> playerItemList;
	int totalEarningsInt;
	int money;
	int energy;

	// SCENEGAME
	int min;
	int hour;
	int day;

	// MAP OBJECT
	vector<Stone*> stones;
	vector<Timber*> timbers;
	vector<Weed*> weeds;
	vector<Tree*> trees;
	vector<vector<HoeDirt*>> dirtArray;
	int cols = 38;
	int rows = 41;

	// ground : 경작지 pos, 마른 상태로 변경
	// crops : 성장상태, pos, GetAcitve 정보 저장?

public:
	SaveLoadData() = default;
	virtual ~SaveLoadData() override;

	void SaveData(DataLoad* sdata);
	void SaveCSV();
	void LoadCSV(DataLoad* ldata);
};

#define SAVELOAD_DATA (SaveLoadData::Instance())