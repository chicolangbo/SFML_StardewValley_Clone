#pragma once
#include "GameObject.h"

class Objects;

class Tree :public GameObject
{
protected:
	
	sf::RectangleShape hitbox;

	string branchId;
	string branchNick;

public:

	Objects* stump; //그루터기
	sf::Sprite branch; //몸통

	Tree(const std::string& name ="", const std::string & branchId = "", const std::string & stumpId = "",
		const std::string& branchNick = "", const std::string& stumpNick = "");
	virtual ~Tree() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	sf::RectangleShape GetHitbox();
};

