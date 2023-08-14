#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "Item.h"

class Player : public SpriteGo
{
protected:
	// 김민지, 230814, 아이템리스트 추가
	std::vector<tagItemInfo> playerItemList;
	//

	AnimationController animation;

	float speed = 500.f;

	sf::Vector2f look; //바라보는 방향
	sf::Vector2f direction;
	sf::Vector2f velocity; //dir*dt

	float accel = 500.f;
	float JumpForce = -750.f; //-250
	float gravity = 1000.f; //500

	bool flipX = false;
	bool isGround = true;

	sf::FloatRect wallBounds;
	sf::Vector2f wallBoundsLT;
	sf::Vector2f wallBoundsRB;

public:
	Player(const std::string& textureId = "", const std::string& n="")
		:SpriteGo(textureId, n) {}
	virtual ~Player() override;

	void SetWallBounds(const sf::FloatRect& bounds);
	bool GetFlipX() const;
	void SetFlipX(bool flip);

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;

	std::vector<tagItemInfo>* GetPlayerItemList() {
		return &playerItemList;
	};
};

