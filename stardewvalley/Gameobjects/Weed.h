#pragma once
#include "Objects.h"
#include "AnimationController.h"

class Weed :public Objects
{
protected:
	AnimationController animation;
	bool bang = false;

public:
	Weed(const std::string& textureId = "", const std::string& n = "", const string& nickName = "")
		: Objects(textureId, n, nickName) {}
	virtual ~Weed() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetBang() { bang = true; }
};

