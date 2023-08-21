#pragma once
#include "SpriteGo.h"
class Stone :public SpriteGo
{
protected:
	int indexX;
	int indexY;
	sf::IntRect texRect;
	sf::Vector2f tileSize;
	sf::Vector2f mapLT;
public:
	Stone(const std::string& textureId = "", const std::string& n = "", const string& nickName = "") : SpriteGo(textureId, n, nickName) {}
	virtual ~Stone() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetType(int x, int y, sf::IntRect tex, sf::Vector2f size);
	void SetMapLT(sf::Vector2f pos);
};

