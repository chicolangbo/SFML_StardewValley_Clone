#include "stdafx.h"
#include "SaveLoadData.h"
#include "Player2.h"

SaveLoadData::~SaveLoadData()
{
}

void SaveLoadData::Save()
{
	// 기존값 파일로 저장
}

void SaveLoadData::Load(Player2* p, int* d, int* h, int* m, float* t)
{
	// TEST SAVE VALUE
	playerItemList.push_back({ ItemId::branch, 1, 5 });
	totalEarningsInt = 30;
	money = 50;
	day = 2;
	hour = 25;
	min = 30; // 60 + 30 = 90 => 2.5*9 = 22.5 => 270 - 22.5 = 248.5
	
	// 저장된 파일 데이터 읽어오기
	// 그대로 로드
	p->LoadData(playerItemList, totalEarningsInt, money);

	// 바뀌어서 로드
	if (hour >= 24)
	{
		energy -= energy * (((hour - 24) * 60 + min)/10) * 2.5f;
	}
	hour = 6;
	min = 0;
	day++;
}