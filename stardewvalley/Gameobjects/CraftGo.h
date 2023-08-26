#pragma once
#include "UiButton.h"
#include "Item.h"

class Player2;

class CraftGo :
    public UiButton
{
protected:
    bool craftPossibility = false;
    std::list<std::pair<ItemId, int>>* ingredients = nullptr;
    int ingredientsCount = 0;

public:
    CraftGo(const std::string& textureId = "", const std::string& n = "", const std::string& nickName = "");
    virtual ~CraftGo() override;

    virtual void Init() override;
    virtual void Release() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;

    void CheckCraftPossiblity(std::list<tagItemInfo>* playerItemList);
    void Craft(Player2* p, ItemId id);
    bool GetCraftPossiblity() { return craftPossibility; }
};

