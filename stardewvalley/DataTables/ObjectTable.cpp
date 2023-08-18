#include "stdafx.h"
#include "rapidcsv.h"
#include "ObjectTable.h"

bool ObjectTable::Load()
{
	rapidcsv::Document doc(filename);

	for (int i = 2; i < doc.GetRowCount(); i++)
	{
		auto rows = doc.GetRow<int>(i);
		table.push_back({ rows[0], rows[1], (float)rows[2], (float)rows[3], (float)rows[4], (float)rows[5], (ObjType)rows[6] });
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

