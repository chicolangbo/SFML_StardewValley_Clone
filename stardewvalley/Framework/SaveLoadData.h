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

	// OBJECT
	// fix obj : �߰��� ����.. �ʷε��� �� ���� �����̶� ���� ����
	vector<Stone*> stones;
	vector<Timber*> timbers;
	vector<Weed*> weeds;
	vector<Tree*> trees;
	// ground : ������ pos, ���� ���·� ����
	// crops : �������, pos, GetAcitve ���� ����?

public:
	SaveLoadData() = default;
	virtual ~SaveLoadData() override;

	void SaveData(DataLoad* sdata);
	void SaveCSV();
	void LoadCSV(DataLoad* ldata);
};

#define SAVELOAD_DATA (SaveLoadData::Instance())