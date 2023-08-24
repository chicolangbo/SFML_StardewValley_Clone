#pragma once
#include "GameObject.h"

class Objects;

class Tree :public GameObject
{
protected:
	
	sf::RectangleShape hitbox;

	string branchId;
	string branchNick;

	int branchHp = 10;
	int stumpHp = 5;

	bool treeRotation = false;
	bool fallingTree = false;
	bool hit = false;
	bool tree = false;

	float rotation = 0.f;
	float time = 0.f;
	float shake = 0.f;
	float direction = 1.f;
	float totalrotation = 0.f;
public:

	Objects* stump; //그루터기
	sf::Sprite branch; //몸통
	//처음에는 브랜치 hp로 다음에는 스텀프 hp로 세팅

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
	bool GetTreeFalling() { return tree; }
	void SetTreeFalling() { tree = false; }
	void TreeRotation() { treeRotation = true; }
	void Hit() { hit = true; }

	string GetBranchNick() { return branchNick; }
};

