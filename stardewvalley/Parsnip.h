#pragma once
#include "Crop.h"
class Parsnip :public Crop
{
protected:
	string lev1Nick;
	string lev2Nick;
	string lev3Nick;
	string lev4Nick;
public:
	Parsnip(const string& textureId = "", const string& n = "", const string& nickname = "");
	virtual ~Parsnip() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
};

