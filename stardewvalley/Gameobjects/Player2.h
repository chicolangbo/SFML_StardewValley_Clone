#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "Scene.h"
#include "Axe.h"
#include "Pickax.h"
#include "Item.h"

class Player2 :  public SpriteGo
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
	sf::Vector2f direction;
	float speed = 500.f;

	bool filpX = false;
	//bool isGround = true;

	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;
	//test
	int item=1;

	//기력 도구 사용시 -2씩 차감
	int maxEnergy = 270;
	int energy = 270;

	bool playingAnimation = false;

	// 김민지, 230814~15, 아이템리스트 추가
	std::list<tagItemInfo> playerItemList;
	std::list<RootingItem*> &rootingItemList;
	int curFundsInt; // 현재 소지금
	int totalEarningsInt; // 총합 자금
	//

public:

	Player2(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Player2() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	// 김민지, 230809, 콜라이더 연동용
	virtual void Draw(sf::RenderWindow& window) override;
	//

	bool GetFlipX() const;
	void SetFlipX(bool filp);

	// 김민지, 230813, 인벤토리에 이미지 복사용
	AnimationController GetAnimation() { return animation; }
	//

	// 김민지, 230814~15, 추가
	std::list<tagItemInfo>* GetPlayerItemList() { return &playerItemList; }
	int* GetCurFundsInt() { return &curFundsInt; }
	int* GetTotalEarningsInt() { return &totalEarningsInt; }
	void AddPlayerItem(ItemId id);
	void SetRootingItems(std::list<RootingItem*> &r) { rootingItemList = r; }
	//
};

