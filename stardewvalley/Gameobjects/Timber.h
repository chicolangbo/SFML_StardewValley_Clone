#pragma once
#include "Objects.h"

class Timber : public Objects
{
protected:

public:
	Timber(const std::string& textureId = "", const std::string& n = "", const string& nickName = "") 
		: Objects(textureId, n, nickName) {}
	virtual ~Timber() override { Release(); }

	//virtual void Init() override;
	//virtual void Reset() override;
	//virtual void Update(float dt) override;

};

