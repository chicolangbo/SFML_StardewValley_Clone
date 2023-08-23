#pragma once
#include "Objects.h"
#include "AnimationController.h"

class Stone :public Objects
{
protected:
	AnimationController animation;
	int hp = 1;
	bool bang = false;
public:
	Stone(const std::string& textureId = "", const std::string& n = "", const string& nickName = "") 
		: Objects(textureId, n, nickName) {}
	virtual ~Stone() override { Release(); }

	virtual void Init() override; 
	virtual void Reset() override; 
	virtual void Update(float dt) override; 
	void SetBang() { bang = true; }
	//virtual void Init() override;
	//virtual void Reset() override;
	//virtual void Update(float dt) override;

};

