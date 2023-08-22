#pragma once
#include "Item.h"
#include "Singleton.h"
#include "SceneGame.h"

class Player2;
class GameObject;
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
	//bool playerDie = false;
	//bool playingAnimation = false;
	//bool one = true;
	//bool boundwall = false;

	// SCENEGAME
	int min; // NEED TO CONTAIN SAVE TIME
	int hour; // NEED TO CONTAIN SAVE TIME
	int day;

	// OBJECT
	// fix obj : 추가로 저장.. 맵로딩할 때 쓰는 파일이랑 같은 형식
	vector<Stone*> stones;
	vector<Timber*> timbers;
	vector<Weed*> weeds;
	vector<Tree*> trees;
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