#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Hoe : public SpriteGo
{
protected:
	AnimationController animation;

	bool flipX;

public:

	Hoe(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Hoe() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void PlayAnimation(sf::String name);
	void SetPostion(sf::Vector2f pos);
	void SetOrigins();

	bool GetFlipX() const;
	void SetFlipX(bool flip);
};

