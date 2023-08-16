#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "Scene.h"
#include "Axe.h"
#include "Pickax.h"
#include "Hoe.h"
#include "Scythe.h"
#include "Wateringcan.h"
#include "Item.h"

enum class Tool
{
	Scythe,
	Axe,
	Pickax,
	Hoe,
	WateringCan,
};

class RootingItem;

class Player2 : public SpriteGo
{
public:
	struct ClipInfo
	{
		std::string idle;
		std::string move;
		bool flipX = false;
		sf::Vector2f point;
	};

protected:
	AnimationController animation;
	Axe axe;
	Pickax pickax;
	Hoe hoe;
	Scythe scythe;
	Wateringcan watering;

	sf::Vector2f direction;
	float speed = 500.f;

	bool filpX = false;
	//bool isGround = true;

	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;
	//test
	Tool item;

	int maxEnergy = 270;
	int energy = 270;
	int money = 500;
	// 김민지, 230816, 추가
	int tempMoney = 0;

	std::vector<sf::FloatRect> wallBounds;
	std::vector<sf::Vector2f> wallBoundsLT;
	std::vector<sf::Vector2f> wallBoundsRB; 

	sf::FloatRect playerBound;

	bool playerDie = false;
	bool playingAnimation = false;
	bool one = true;
	bool boundwall = false;
	
	std::list<tagItemInfo> playerItemList;
	std::list<RootingItem*>*rootingItemList;
	int totalEarningsInt = 500; // ���� �ڱ�

public:

	Player2(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Player2() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	bool GetFlipX() const;
	void SetFlipX(bool filp);

	int GetEnergy() { return energy; }
	int* GetMoney() { return &money; }

	void SetWallBounds(const sf::FloatRect& bounds);
	void SetCollider(const sf::FloatRect& coll);

	AnimationController GetAnimation() { return animation; }

	std::list<tagItemInfo>* GetPlayerItemList() { return &playerItemList; }
	int* GetTotalEarningsInt() { return &totalEarningsInt; }
	void AddPlayerItem();
	void SetRootingItems(std::list<RootingItem*>*r) { rootingItemList = r; }
	void MoneyUpdate();
};

