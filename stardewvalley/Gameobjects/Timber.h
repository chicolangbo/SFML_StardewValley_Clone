#pragma once
#include "Objects.h"

class Timber : public Objects
{
protected:
	/*int indexX;
	int indexY;
	sf::IntRect texRect;
	sf::Vector2f tileSize;
	sf::Vector2f mapLT;*/
public:
	Timber(const std::string& textureId = "", const std::string& n = "", const string& nickName = "") 
		: Objects(textureId, n, nickName) {}
	virtual ~Timber() override { Release(); }

	//virtual void Init() override;
	//virtual void Reset() override;
	//virtual void Update(float dt) override;

	//void SetType(int x, int y, sf::IntRect tex, sf::Vector2f size);
	//void SetMapLT(sf::Vector2f pos);
};

