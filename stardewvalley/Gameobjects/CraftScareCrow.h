#pragma once
#include "CraftGo.h"

class CraftScareCrow :
    public CraftGo
{
protected:
    std::list<std::pair<ItemId, int>> scareCrawIngredients;
    ItemId id = ItemId::craftScareCrow;

public:
    CraftScareCrow(const std::string& textureId = "", const std::string& n = "", const std::string& nickName = "");
    virtual ~CraftScareCrow() override;

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;
    ItemId GetId() { return id; }
};
