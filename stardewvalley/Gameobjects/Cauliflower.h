#pragma once
#include "Crop.h"
#include "ObjectPool.h"

class Cauliflower : public Crop
{
protected:
	ObjectPool<Cauliflower>* pool = nullptr;
public:
	Cauliflower(const string& textureId = "", const string& n = "", const string& nickname = "");
	virtual ~Cauliflower() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;

	void SetPool(ObjectPool<Cauliflower>* pool) { this->pool = pool; }
};

