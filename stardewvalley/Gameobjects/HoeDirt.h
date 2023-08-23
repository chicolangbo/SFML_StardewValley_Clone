#pragma once
#include "GameObject.h"

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

public:
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

	void SetIsWatered(bool is) { isWatered = is; }
	void SetIndex(int x, int y) { indexX = x; indexY = y; }
	void SetPlantedCrop(bool is) { plantedCrop = is; }
	void SetCurrentDay(bool is) { currentDay = is; }

	sf::Vector2i GetIndex() { return sf::Vector2i(indexX, indexY); }
	bool GetIsWatered() { return isWatered; }
	bool GetIsPlanted() { return plantedCrop; }
};

