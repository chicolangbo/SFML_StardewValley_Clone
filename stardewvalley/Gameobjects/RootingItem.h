#pragma once
#include "SpriteGo.h"
#include "Player2.h"


class RootingItem : public SpriteGo
{
protected:
	ItemId id;

	Player2* player;


	sf::Vector2f pos;
	sf::Vector2f look;
	sf::Vector2f direction;

	//sf::Vector2f pongDirection;

	float speed = 500.f;

public:
	RootingItem(ItemId id, const std::string& textureId = "", const std::string& n = "", const std::string& nickName = "");
	~RootingItem();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetPlayer(Player2* p) { player = p; }
	//

	ItemId GetRootingItemId() { return id; }
};

