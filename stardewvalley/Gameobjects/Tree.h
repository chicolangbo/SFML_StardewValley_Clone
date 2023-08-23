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
	float rotation = 0.f;
	float time = 0.f;
public:

	Objects* stump; //�׷��ͱ�
	sf::Sprite branch; //����
	//ó������ �귣ġ hp�� �������� ������ hp�� ����

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

	void TreeRotation() { treeRotation = true; }
};
