#pragma once
#include "DataTable.h"
#include "Wall.h"

struct WallInfo
{
    Wall::Types wallType;
    float left;
    float top;
    float width;
    float height;
};

class WallTable :
    public DataTable
{
protected:
    std::unordered_map<Wall::Types, WallInfo> table;

public:
    // ±è¹ÎÁö, 230809, Ãß°¡
    int size;
    //

    WallTable() : DataTable(DataTable::Ids::Wall) {};
    virtual ~WallTable() override = default;

    virtual bool Load() override;
    virtual void Release() override;

    const WallInfo& Get(Wall::Types t);
};

