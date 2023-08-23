#include "stdafx.h"
#include "CropTable.h"
#include "rapidcsv.h"

/*struct cropInfo
{
	CropId cropId;
	string Name;
	int period[4];
	string seedNick[2];
	string nickName[4];
};*/

bool CropTable::Load()
{
	string filename = "tables/CropTable.csv";

	rapidcsv::Document doc(filename);

	auto keys = doc.GetRow<string>(0);

	auto names = doc.GetColumn<string>(0);
	auto ids = doc.GetColumn<int>(1);

	auto period1 = doc.GetColumn<int>(2);
	auto period2 = doc.GetColumn<int>(3);
	auto period3= doc.GetColumn<int>(4);
	auto period4 = doc.GetColumn<int>(5);

	auto seedNick1 = doc.GetColumn<string>(6);
	auto seedNick2 = doc.GetColumn<string>(7);

	auto Nick1 = doc.GetColumn<string>(8);
	auto Nick2 = doc.GetColumn<string>(9);
	auto Nick3 = doc.GetColumn<string>(10);
	auto Nick4 = doc.GetColumn<string>(11);

	
	for (int i = 0; i < ids.size(); i++)
	{
		cropInfo cInfo
		{
			(CropId)ids[i], names[i],
			{ period1[i], period2[i], period3[i], period4[i] },
			{ seedNick1[i], seedNick2[i]},
			{ Nick1[i], Nick2[i], Nick3[i], Nick4[i] },
		};
		table.insert({ (CropId)ids[i], cInfo });
	}
	return true;
}

void CropTable::Release()
{
    table.clear();
}

const cropInfo& CropTable::Get(CropId id) const
{
	auto find = table.find(id);
	if (find == table.end())
	{
		cout << "ERR: Failed to Data Table Load" << endl;
		exit(-1);
	}
	return find->second;
}
