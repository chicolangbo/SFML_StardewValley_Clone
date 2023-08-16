#include "stdafx.h"
#include "QuickInventory.h"
#include "Slot.h"  
#include "InputMgr.h"

GameObject* QuickInventory::AddUi(GameObject* go)
{
	if (!Exist(go))
	{
		quickinvenUi.push_back(go); 
	}
	return go;
}

bool QuickInventory::Exist(GameObject* go)
{
	for (auto& m : quickinvenUi) 
	{
		if (m == go)
		{
			return true;
		}
	}
	return false;
}

QuickInventory::QuickInventory(const std::string& n)
	:GameObject(n), quickInven("graphics/box1.png", "invenBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE)
{
	AddUi(&quickInven);
	for (int i = 0; i < 12; ++i)
	{
		std::string num = to_string(i);
		quickslot.push_back(new Slot("graphics/MenuTiles.png", "invenCell" + num, "invenCell"));
		quickslot[i]->slotIndex = i;
		quickslot[i]->SetOrigin(Origins::MC);
		quickslot[i]->colliderOnOff = false;
		AddUi(quickslot[i]);
	}
}

QuickInventory::~QuickInventory()
{
	//동적할당 한 것들만 delete
	Release(); 
}

void QuickInventory::Init()
{
	for (auto i : quickinvenUi)
	{
		i->Init();
	}
}

void QuickInventory::Reset()
{
	for (auto m : quickinvenUi)
	{
		m->Reset(); 
	}

	quickInven.SetSize({ 1040.f,125.f });
	quickInven.SetOrigin(Origins::MC);
	quickInven.SetPosition(position.x,position.y+140.f);
	quickInven.sortLayer = 120;

	for (int i = 0; i < 12; ++i)
	{
		quickslot[i]->SetPosition({ 503.f + (i * 83.f),1025.f });
		quickslot[i]->sortLayer = 121;
	}
}

void QuickInventory::Release()
{
	for (auto it : quickslot)
	{
		delete it;
	}
	
	quickinvenUi.clear();
}

void QuickInventory::Update(float dt)
{
	for (auto m : quickinvenUi) 
	{
		m->Update(dt);
	}
	/*sf::Vector2f pos = INPUT_MGR.GetMousePos();
	std::cout << pos.x << " " << pos.y << std::endl;*/
}

void QuickInventory::Draw(sf::RenderWindow& window)
{
	for (auto m : quickinvenUi) 
	{
		m->Draw(window);
	}
}
