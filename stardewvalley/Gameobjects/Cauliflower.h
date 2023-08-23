#pragma once
#include "Crop.h"
class Cauliflower : public Crop
{
protected:

public:
	Cauliflower(const string& textureId = "", const string& n = "", const string& nickname = "");
	virtual ~Cauliflower() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
};

