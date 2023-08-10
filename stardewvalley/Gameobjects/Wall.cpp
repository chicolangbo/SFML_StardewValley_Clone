#include "stdafx.h"
#include "Wall.h"
#include "WallTable.h"
#include "DataTableMgr.h"
#include "InputMgr.h"

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
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num0))
	{
		if (colliderOnOff)
		{
			colliderOnOff = false;
		}
		else
		{
			colliderOnOff = true;
		}
	}
	//GameObject::Update(dt);
}

void Wall::Draw(sf::RenderWindow& window)
{
	//GameObject::Draw(window);
	//if (colliderOnOff)
	{
		for (auto it : Walls)
		{
			window.draw(it);
		}		
	}
}

void Wall::SetPos()
{
	int size = DATATABLE_MGR.Get<WallTable>(DataTable::Ids::Wall)->size;
	for (int i = 0; i < size; i++)
	{
		if (locationType == Location::Home && i>10)
		{
			const WallInfo& info = DATATABLE_MGR.Get<WallTable>(DataTable::Ids::Wall)->Get((Types)i);
			sf::RectangleShape rect; 
			rect.setSize({ info.width, info.height });
			rect.setScale(4.f, 4.f);
			rect.setOrigin(0, 0);
			rect.setPosition(info.left, info.top);
			rect.setOutlineThickness(0.5f);
			rect.setOutlineColor(sf::Color::Red);
			rect.setFillColor(sf::Color::Transparent);
			Walls.push_back(rect);
		}
		else if (locationType == Location::Shop && i < 10)
		{
			const WallInfo& info = DATATABLE_MGR.Get<WallTable>(DataTable::Ids::Wall)->Get((Types)i);
			sf::RectangleShape rect;
			rect.setSize({ info.width, info.height });
			rect.setScale(4.f, 4.f);
			rect.setOrigin(0, 0);
			rect.setPosition(info.left*4, info.top*4);
			rect.setOutlineThickness(0.5f);
			rect.setOutlineColor(sf::Color::Red);
			rect.setFillColor(sf::Color::Transparent);
			Walls.push_back(rect);

		}
	}
}

void Wall::SetType(Location l)
{
	locationType = l;
}
