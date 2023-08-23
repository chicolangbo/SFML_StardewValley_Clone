#pragma once
#include "DataTable.h"
#include "Crop.h"

struct cropInfo
{
	CropId cropId;
	string Name;
	int period[4];
	string seedNick[2];
	string nickName[4];
};
class CropTable : public DataTable
{
protected:
	unordered_map<CropId, cropInfo> table;
public:
	CropTable() : DataTable(DataTable::Ids::Crop) {};
	virtual ~CropTable() override = default;

	virtual bool Load() override;
	virtual void Release() override;

	const cropInfo& Get(CropId id) const;
};

