#pragma once
#include "SpriteGo.h"
class Stone :public SpriteGo
{
protected:

public:
	Stone(const std::string& textureId = "", const std::string& n = "", const string& nickName = "") : SpriteGo(textureId, n, nickName) {}
	virtual ~Stone() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

