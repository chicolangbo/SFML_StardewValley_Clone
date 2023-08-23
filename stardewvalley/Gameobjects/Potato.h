#pragma once
#include "Crop.h"
class Potato : public Crop
{
protected:

public:
	Potato(const string& textureId = "", const string& n = "", const string& nickname = "");
	virtual ~Potato() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
};

