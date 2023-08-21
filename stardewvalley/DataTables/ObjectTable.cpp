#include "stdafx.h"
#include "rapidcsv.h"
#include "ObjectTable.h"

bool ObjectTable::Load()
{
	rapidcsv::Document doc(filename);

	for (int i = 2; i < doc.GetRowCount(); i++)
	{
		auto rows = doc.GetRow<int>(i);
		ObjectInfo oInfo
		{
			rows[1], rows[2], (float)rows[3], (float)rows[4], (float)rows[5], (float)rows[6], (ObjType)rows[7]
		};
		table.insert({ rows[0], oInfo});
	}
	return true;
}

void ObjectTable::Release()
{
	table.clear();
}

bool ObjectTable::Save(vector<ObjectInfo> objects, int col, int row)
{
	std::ofstream outputFile(filename);

	if (!outputFile.is_open())
	{
		cout << "ERR: 파일을 열 수 없습니다." << endl;
		return false;
	}

	// 파일 헤더
	outputFile << "cols,rows" << endl;
	outputFile << col << "," << row << endl;

	outputFile << "indexX,indexY,left,top,width,height,type" << endl;

	for (int i = 0; i < objects.size(); ++i)
	{
		auto objs = objects[i];
		outputFile << objs.indexX << "," << objs.indexY << "," << objs.left << "," << objs.top << "," <<
			objs.width << "," << objs.height << "," << (int)objs.type << endl;
	}

	outputFile.close();
	return true;
}

const ObjectInfo& ObjectTable::Get(ObjType id) const
{
	//auto find = table.find(id);
	//if (find == table.end()) //존재하지 않을 때
	//{
	//	cout << "ERR: Failed to Data Table Load" << endl;
	//	exit(-1);
	//}
	//return find->second;
	return table.find(0)->second;
}

