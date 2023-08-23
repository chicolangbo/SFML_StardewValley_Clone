#pragma once
#include "Objects.h"
#include "AnimationController.h"

class Timber : public Objects
{
protected:
	AnimationController animation;
	bool bang = false;
	
public:
	Timber(const std::string& textureId = "", const std::string& n = "", const string& nickName = "") 
		: Objects(textureId, n, nickName) {}
	virtual ~Timber() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetBang() { bang = true; }
};

