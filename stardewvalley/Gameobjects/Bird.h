#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Bird : public SpriteGo
{
protected:

	AnimationController animation;

public:

	Bird(const std::string& textureId = "", const std::string& n = "")
		:SpriteGo(textureId, n) {}
	virtual ~Bird() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

