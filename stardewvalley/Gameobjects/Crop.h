#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

struct CropSaveData
{
	CropId id;
	int date;
	int day;
	int currentday;
	int level;
	sf::Vector2i index;
	bool isWatered;
	int sortLayer;
	int sortOrder;
};

class HoeDirt;

class Crop :public SpriteGo
{
protected:

	int date; //심은 날짜
	int day; //성장중인 날
	int currentday; //현재 날짜
	int level; //성장단계
	sf::Vector2i index; //위치
	int allPeriod = 0; //수확까지 성장 기간
	bool canHarvest = false;
	bool isWatered; //물줬는지

	CropSaveData cropSaveData;

	CropId id;
	int period[4];
	string seedNick[2];
	string nickName[4];

	HoeDirt* dirtTile = nullptr; //심겨진 타일

	sf::Vector2f tileSize;

	AnimationController animation;
	float time = 0;
	float animationTime = 8 / 12;

public:
	bool bang;
	bool load = false;

	Crop(const string& textureId = "", const string& n = "", const string& nickname = "");
	virtual ~Crop() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;

	void SetIndex(int x, int y);
	void SetTileSize(sf::Vector2f size) { tileSize = size; }
	void SetType(CropId id);
	void SetDirtTile(HoeDirt* tile);
	void SetDate(int date);
	void SetIsWatered(bool is) { isWatered = is; }
	void LoadData(CropLoadData ldata);

	void LevelUp();
	bool GetCanHarvest() { return canHarvest; }
	CropId GetCropId() { return id; }

	//TEST CODE
	void FullLevUp();
	
	sf::Vector2i GetIndex() { return index; }
	CropSaveData GetLoadData();
};

