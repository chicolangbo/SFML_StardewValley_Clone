#pragma once
#include "Objects.h"
class Weed :public Objects
{
protected:

public:
	Weed(const std::string& textureId = "", const std::string& n = "", const string& nickName = "")
		: Objects(textureId, n, nickName) {}
	virtual ~Weed() override { Release(); }
};

