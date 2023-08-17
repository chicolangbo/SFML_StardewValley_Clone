#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
class Scythe : public SpriteGo
{
protected:
	AnimationController animation;

	bool flipX;

public:

	Scythe(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Scythe() override { Release(); }

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
