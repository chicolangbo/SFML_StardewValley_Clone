#pragma once
#include "GameObject.h"

class Wall : public GameObject
{
public:
	enum class Types
	{
		Shop_L,
		Shop_T1,
		Shop_T2,
		Shop_R1,
		Shop_R2,
		Shop_B1,
		Shop_B2,
		Shop_B3,
		Shop_B4,
		Shop_B5,
		Home,
	};

	enum class Location
	{
		Shop,
		Home
	};

protected:
	std::vector<sf::RectangleShape> Walls;
	Types wallType;
	Location locationType;
	float left;
	float top;
	float width;
	float height;
	bool colliderOnOff;

public:
	Wall(const std::string& n = "");
	virtual ~Wall() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetPos();
	void SetType(Location l);
};

