#pragma once
#include "SpriteGo.h"
class Objects :public SpriteGo
{
protected:

	int indexX;
	int indexY;
	sf::IntRect texRect;
	sf::Vector2f tileSize;
	sf::Vector2f mapLT;
	int hp;

public:
	Objects(const std::string& textureId = "", const std::string& n = "", const string& nickName = "") 
		: SpriteGo(textureId, n, nickName) {}
	virtual ~Objects() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	virtual void SetHp(int h) { hp = h; }            
	virtual int GetHp() { return hp; }
	virtual void Hit(int d) { hp -= d; }

	void SetType(int x, int y, sf::IntRect tex, sf::Vector2f size);
	void SetMapLT(sf::Vector2f pos);

	sf::Vector2f GetIndex() { return sf::Vector2f(indexX, indexY); }
	sf::IntRect GetTexRect() { return texRect; }
};

