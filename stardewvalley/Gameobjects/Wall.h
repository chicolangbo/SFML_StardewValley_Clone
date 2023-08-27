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
		Home_L,
		Home_T,
		Home_M1,
		Home_M2,
		Home_M3,
		Home_M4,
		Home_M5,
		Home_R,
		Home_B1,
		Home_B2,
		Home_B3,
		Home_B4
	};

protected:
	
	Types wallType;
	Location locationType;
	float left;
	float top;
	float width;
	float height;
	bool colliderOnOff = false;

	struct wallstruct
	{
		sf::RectangleShape rect;
		Types wallType;
	};

public:
	//임형준, 230814, 플레이어에 정보를 넘겨줄 용도로 protected->public으로 변경
	//std::vector<sf::RectangleShape> Walls; 
	std::vector<wallstruct> Walls;
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

