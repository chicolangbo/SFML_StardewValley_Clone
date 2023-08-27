#pragma once
#include "GameObject.h"

class Crop;

class HoeDirt :public GameObject
{
protected:

	string textureId;
	string dirtNick;
	string waterNick;

	int indexX = 0;
	int indexY = 0;
	int day = 0; //땅이 파진 날짜
	bool plantedCrop = false;
	bool isWatered = false;
	int currentDay = 0;

	CropId cropId;
	Crop* crop;

public:
	bool load = false;
	sf::Sprite dirt;
	sf::Sprite waterDirt;

	HoeDirt(const string& n = "", const string& textureId = "", const string& dirtNick = "", const string& waterNick = "");
	virtual ~HoeDirt() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	void SetIsWatered(bool is); 
	void SetIndex(int x, int y) { indexX = x; indexY = y; }
	//void SetPlantedCrop(bool is) { plantedCrop = is; }
	void SetCurrentDay(bool is) { currentDay = is; }
	//void SetCropId(CropId id) { cropId = id; }
	void PlantCrop(Crop* c);
	void RemoveCrop();

	void SetDirtTex(string name);
	void SetWaterDirtTex(string name);

	sf::Vector2i GetIndex() { return sf::Vector2i(indexX, indexY); }
	bool GetIsWatered() { return isWatered; }
	bool GetIsPlanted() { return plantedCrop; }
	Crop* GetCrop() { return crop; }
	CropId GetCropId() { return cropId; }
};

