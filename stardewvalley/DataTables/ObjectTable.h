#pragma once
#include "DataTable.h"

struct ObjectInfo
{
	int indexX;
	int indexY;
	float left;
	float top;
	float width;
	float height;
	ObjType type;
};

class ObjectTable :
    public DataTable
{
protected:
	unordered_map<int, ObjectInfo> table;
	string filename = "tables/newMapObj.csv";
public:
	ObjectTable() : DataTable(DataTable::Ids::Object) {};
	virtual ~ObjectTable() override = default;

	virtual bool Load() override;
	virtual void Release() override;

	unordered_map<int, ObjectInfo> GetTable() { return table; };
	bool Save(vector<ObjectInfo> objects, int col, int row);

	const ObjectInfo& Get(ObjType id) const;
};

