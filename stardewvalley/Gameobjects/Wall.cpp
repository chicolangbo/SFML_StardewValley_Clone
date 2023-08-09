#include "stdafx.h"
#include "Wall.h"
#include "WallTable.h"
#include "DataTableMgr.h"

Wall::Wall(const std::string& n)
	:GameObject(n)
{
}

Wall::~Wall()
{
}

void Wall::Init()
{
	//GameObject::Init();
}

void Wall::Release()
{
	GameObject::Release();
}

void Wall::Reset()
{
	//GameObject::Reset();
}

void Wall::Update(float dt)
{
	//GameObject::Update(dt);
}

void Wall::Draw(sf::RenderWindow& window)
{
	//GameObject::Draw(window);
}

void Wall::SetPos(Types t)
{
	for (int i = 0; i < DATATABLE_MGR.Get<WallTable>(DataTable::Ids::Wall)->size; i++)
	{
		if (locationType == Location::Home && i<10)
		{
			const WallInfo& info = DATATABLE_MGR.Get<WallTable>(DataTable::Ids::Wall)->Get((Types)i);
			sf::RectangleShape rect; 
			rect.setSize({ info.width, info.height });
			rect.setOrigin(0, 0);
			rect.setPosition(info.left, info.top);
			Walls.push_back(rect);
		}
		else if (locationType == Location::Shop && i >= 10)
		{
			const WallInfo& info = DATATABLE_MGR.Get<WallTable>(DataTable::Ids::Wall)->Get((Types)i);
			sf::RectangleShape rect;
			rect.setSize({ info.width, info.height });
			rect.setOrigin(0, 0);
			rect.setPosition(info.left, info.top);
			Walls.push_back(rect);

		}
	}
}

void Wall::SetType(Location l)
{
	locationType = l;
}
