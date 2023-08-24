#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class EffectGo : public SpriteGo
{
protected:
	std::string name;
	std::string animationName; 
	AnimationController animation;
	bool play = false;

public:
	EffectGo(const std::string& textureId , const std::string& n );
		
	virtual ~EffectGo() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void SetPlay() { play = true; }
};

