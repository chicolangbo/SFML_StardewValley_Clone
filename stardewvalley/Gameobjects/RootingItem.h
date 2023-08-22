#pragma once
#include "SpriteGo.h"

class RootingItem : public SpriteGo
{
protected:
	ItemId id;

public:
	RootingItem(ItemId id, const std::string& textureId = "", const std::string& n = "", const std::string& nickName = "");
	~RootingItem();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	//

	ItemId GetRootingItemId() { return id; }
};

