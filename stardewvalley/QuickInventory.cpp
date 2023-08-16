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
	:GameObject(n), quickInven("graphics/box1.png", "invenBox", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE),
	mark("graphics/MenuTiles.png","Mark","Mark")
{
	
	AddUi(&quickInven);

	for (int i = 0; i < 12; ++i)
	{
		std::string num = to_string(i);
		quickslots.push_back(new Slot("graphics/MenuTiles.png", "invenCell" + num, "invenCell"));
		quickslots[i]->slotIndex = i;
		quickslots[i]->SetOrigin(Origins::MC);
		quickslots[i]->colliderOnOff = false;
		AddUi(quickslots[i]);
	}

	AddUi(&mark);

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

	quickInven.SetSize({ 895.f,125.f });
	quickInven.SetOrigin(Origins::MC);
	quickInven.SetPosition(position.x,position.y+140.f);
	quickInven.sortLayer = 120;

	for (int i = 0; i < 12; ++i)
	{

		quickslots[i]->SetPosition({ 575.f + (i * 70.f),1025.f });
		quickslots[i]->sortLayer = 121;
	}
	mark.SetOrigin(Origins::MC); 
	mark.SetPosition(quickslots[0]->GetPosition().x, quickslots[0]->GetPosition().y);
	mark.colliderOnOff = false; 
	mark.sortLayer = 130; 
}

void QuickInventory::Release()
{
	for (auto it : *quickslot)
	{
		delete it;
	}
	
	quickinvenUi.clear();
}

void QuickInventory::Update(float dt)
{
	for (int i = 0; i < 12; ++i)
	{
		quickslots[i]->itemIcon = (*quickslot)[i]->itemIcon; //GEt함수로 수정해야함  
	}

	for (auto m : quickinvenUi)
	{
		m->Update(dt);
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		mark.SetPosition(quickslots[0]->GetPosition());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	{
		mark.SetPosition(quickslots[1]->GetPosition());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
	{
		mark.SetPosition(quickslots[2]->GetPosition());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num4))
	{
		mark.SetPosition(quickslots[3]->GetPosition());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num5))
	{
		mark.SetPosition(quickslots[4]->GetPosition());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num6))
	{
		mark.SetPosition(quickslots[5]->GetPosition());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num7))
	{
		mark.SetPosition(quickslots[6]->GetPosition());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num8))
	{
		mark.SetPosition(quickslots[7]->GetPosition());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num9))
	{
		mark.SetPosition(quickslots[8]->GetPosition());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num0))
	{
		mark.SetPosition(quickslots[9]->GetPosition());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Hyphen))
	{
		mark.SetPosition(quickslots[10]->GetPosition());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Equal))
	{
		mark.SetPosition(quickslots[11]->GetPosition());
	}
		
}

void QuickInventory::Draw(sf::RenderWindow& window)
{
	for (auto m : quickinvenUi) 
	{
		m->Draw(window);
	}
}
