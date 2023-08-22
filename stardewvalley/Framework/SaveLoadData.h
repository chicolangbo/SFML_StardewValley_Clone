#pragma once
#include "Item.h"
#include "Singleton.h"

class Player2;
class GameObject;

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
	// REMOVEGO 한 오브젝트들만 INIT할때 생기는 오브젝트에서 삭제하는 게 나을듯
	std::list<GameObject*> removeGameObjects;

public:
	SaveLoadData() = default;
	virtual ~SaveLoadData();

	void Save();
	void Load(Player2* p, int* d, int* h, int* m, float* t);
};

#define SAVELOAD_DATA (SaveLoadData::Instance())