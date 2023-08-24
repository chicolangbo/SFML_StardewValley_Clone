#pragma once
#include "Item.h"
#include "Singleton.h"
#include "SceneGame.h"
#include "ObjectTable.h"

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

	// ground : 경작지 pos, 마른 상태로 변경
	// crops : 성장상태, pos, GetAcitve 정보 저장?

public:
	unordered_map<int, ObjectInfo> table;
	SaveLoadData() = default;
	virtual ~SaveLoadData() override;

	void SaveCSV(DataLoad* sdata);
	void LoadCSV(DataLoad* ldata);
};

#define SAVELOAD_DATA (SaveLoadData::Instance())