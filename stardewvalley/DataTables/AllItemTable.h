#pragma once
#include "DataTable.h"
#include "Item.h"

struct ItemInfo
{
    ItemId itemId;
    ITEM itemkind;
    std::string name_e;
    std::string name_k;
    std::string nickName = "";
    std::string description_e;
    std::string description_k;
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

    AllItemTable() : DataTable(DataTable::Ids::AllItem) {};
    virtual ~AllItemTable() override = default;

    virtual bool Load() override;
    virtual void Release() override;

    const ItemInfo* Get(ItemId);
    const std::wstring GetUniName(ItemId id);
    const std::wstring GetUniDescription(ItemId id);
    wstring multibyte_to_uni(const std::string& str);
};

