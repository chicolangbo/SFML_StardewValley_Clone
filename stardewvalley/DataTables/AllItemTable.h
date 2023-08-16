#pragma once
#include "DataTable.h"
#include "Item.h"

struct ItemInfo
{
    ItemId itemId;
    ITEM itemkind;
    std::string name;
    std::string nickName = "";
    std::string description;
    std::string resource;
    int price;
};

class AllItemTable :
    public DataTable
{
protected:

public:
    std::unordered_map<ItemId, ItemInfo> table;
    int size;

    AllItemTable() : DataTable(DataTable::Ids::Wall) {};
    virtual ~AllItemTable() override = default;

    virtual bool Load() override;
    virtual void Release() override;

    const ItemInfo* Get(ItemId);
};

