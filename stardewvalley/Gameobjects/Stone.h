#pragma once
#include "Objects.h"
class Stone :public Objects
{
protected:
	/*int indexX;
	int indexY;
	sf::IntRect texRect;
	sf::Vector2f tileSize;
	sf::Vector2f mapLT;*/
	int hp = 1;
public:
	Stone(const std::string& textureId = "", const std::string& n = "", const string& nickName = "") 
		: Objects(textureId, n, nickName) {}
	virtual ~Stone() override { Release(); }
	//virtual void Init() override;
	//virtual void Reset() override;
	//virtual void Update(float dt) override;

};

