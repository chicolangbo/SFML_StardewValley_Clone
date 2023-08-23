#pragma once
#include "SpriteGo.h"

class HoeDirt;

class Crop :public SpriteGo
{
protected:

	int date; //���� ��¥
	int day; //�������� ��
	int currentday; //���� ��¥
	int level; //����ܰ�
	sf::Vector2i index; //��ġ
	int allPeriod; //��Ȯ���� ���� �Ⱓ
	bool isWatered; //�������

	CropId id;
	int period[4];
	string seedNick[2];
	string nickName[4];

	HoeDirt* dirtTile = nullptr; //�ɰ��� Ÿ��

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
	void SetType(CropId id);
	void SetDirtTile(HoeDirt* tile);
	void SetDate(int date);
	void SetIsWatered(bool is) { isWatered = is; }

	void LevelUp();
	
	sf::Vector2i GetIndex() { return index; }
};
