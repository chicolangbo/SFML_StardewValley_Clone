#pragma once
#include "Crop.h"
#include "ObjectPool.h"

class Potato : public Crop
{
protected:
	ObjectPool<Potato>* pool = nullptr;
public:
	Potato(const string& textureId = "", const string& n = "", const string& nickname = "");
	virtual ~Potato() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;

	void SetPool(ObjectPool<Potato>* pool) { this->pool = pool; }
};

