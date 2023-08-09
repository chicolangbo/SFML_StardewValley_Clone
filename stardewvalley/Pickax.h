#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
class Pickax : public SpriteGo
{
protected:
	AnimationController animation;

	bool playingAnimation = false;

public:

	Pickax(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Pickax() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void PlayAnimation(sf::String name);
	void SetPostion(sf::Vector2f pos);
	void SetOrigins();
};

