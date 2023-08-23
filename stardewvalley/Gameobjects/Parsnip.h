#pragma once
#include "Crop.h"
class Parsnip :public Crop
{
protected:

public:
	Parsnip(const string& textureId = "", const string& n = "", const string& nickname = "");
	virtual ~Parsnip() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
};

