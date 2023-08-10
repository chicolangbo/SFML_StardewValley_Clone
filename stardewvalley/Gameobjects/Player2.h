#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "Scene.h"
#include "Axe.h"
#include "Pickax.h"
#include "Hoe.h"
#include "Scythe.h"

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
	Hoe hoe;
	Scythe scythe;

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

	bool playerDie = false;
	bool playingAnimation = false;

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



};

