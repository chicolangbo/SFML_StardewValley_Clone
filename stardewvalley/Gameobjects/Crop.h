#pragma once
#include "SpriteGo.h"

class HoeDirt;

class Crop :public SpriteGo
{
protected:

	int date; //심은 날짜
	int day; //성장중인 날
	int level; //성장단계
	sf::Vector2i index; //위치
	int period; //수확까지 성장 기간

	HoeDirt* dirtTile; //심겨진 타일

	sf::Vector2f tileSize;

public:
	Crop(const string& textureId = "", const string& n = "", const string& nickname = "");
	virtual ~Crop() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;

	void SetIndex(int x, int y);
	void SetTileSize(sf::Vector2f size) { tileSize = size; }
};

