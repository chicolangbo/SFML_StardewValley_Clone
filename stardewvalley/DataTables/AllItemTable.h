#pragma once
#include "DataTable.h"
#include "Item.h"

class AllItemTable :
    public DataTable
{
protected:
    std::unordered_map<std::string, tagItemInfo> table;

public:
    int size;

    AllItemTable() : DataTable(DataTable::Ids::Wall) {};
    virtual ~AllItemTable() override = default;

    virtual bool Load() override;
    virtual void Release() override;

    const tagItemInfo* Get(std::string);
};

