#include "stdafx.h"
#include "QuickInventory.h"
#include "Slot.h"  
#include "InputMgr.h"
#include "AllItemTable.h"
#include "DataTableMgr.h"

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
	SetPlayerItemList();
	ItemIconSetUp();

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
	quickInven.sortLayer = 150;

	for (int i = 0; i < 12; ++i)
	{

		quickslots[i]->SetPosition({ 575.f + (i * 70.f),1025.f });
		quickslots[i]->sortLayer = 150;
	}
	mark.SetOrigin(Origins::MC); 
	mark.SetPosition(quickslots[0]->GetPosition().x, quickslots[0]->GetPosition().y);
	mark.colliderOnOff = false; 
	mark.sortLayer = 130; 

	itemid = ItemId::none;
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
		quickslots[i]->SetItemIcon((*quickslot)[i]->GetItemIcon());   
		quickslots[i]->SetItemId((*quickslot)[i]->GetItemId());  
	}
	ItemIndexUpdate();
	IconUpdate();    


	for (auto m : quickinvenUi)
	{
		m->Update(dt);
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		mark.SetPosition(quickslots[0]->GetPosition());

		itemid = quickslots[0]->GetItemId();

		/*if (quickslots[0]->GetItemId() == ItemId::pick) 
		{
			itemid = ItemId::pick;
		}
		else if (quickslots[0]->GetItemId() == ItemId::ax)
		{
			itemid = ItemId::ax;
		}
		else if (quickslots[0]->GetItemId() == ItemId::homi)
		{
			itemid = ItemId::homi;
		}
		else if (quickslots[0]->GetItemId() == ItemId::hook)
		{
			itemid = ItemId::hook;
		}
		else if (quickslots[0]->GetItemId() == ItemId::waterCan)
		{
			itemid = ItemId::waterCan;
		}
		else
		{
			itemid = ItemId::none;
		}*/
		
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	{
		mark.SetPosition(quickslots[1]->GetPosition());
		itemid = quickslots[1]->GetItemId();
		
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
	{
		mark.SetPosition(quickslots[2]->GetPosition());
		itemid = quickslots[2]->GetItemId();
		
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num4))
	{
		mark.SetPosition(quickslots[3]->GetPosition());
		itemid = quickslots[3]->GetItemId();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num5))
	{
		mark.SetPosition(quickslots[4]->GetPosition());
		itemid = quickslots[4]->GetItemId();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num6))
	{
		mark.SetPosition(quickslots[5]->GetPosition());
		itemid = quickslots[5]->GetItemId();
		
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num7))
	{
		mark.SetPosition(quickslots[6]->GetPosition());
		itemid = quickslots[6]->GetItemId();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num8))
	{
		mark.SetPosition(quickslots[7]->GetPosition());
		itemid = quickslots[7]->GetItemId();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num9))
	{
		mark.SetPosition(quickslots[8]->GetPosition());
		itemid = quickslots[8]->GetItemId();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num0))
	{
		mark.SetPosition(quickslots[9]->GetPosition());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Hyphen))
	{
		mark.SetPosition(quickslots[10]->GetPosition());
		itemid = quickslots[10]->GetItemId();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Equal))
	{
		mark.SetPosition(quickslots[11]->GetPosition());
		itemid = quickslots[11]->GetItemId();
	}
}

void QuickInventory::Draw(sf::RenderWindow& window)
{
	for (auto m : quickinvenUi) 
	{
		m->Draw(window);
	}
}

void QuickInventory::IconUpdate()
{
	for (Slot* sl : quickslots)
	{
		for (tagItemInfo& pl : *playerItemList)
		{
			if (pl.index == sl->slotIndex)
			{
				auto foundItem = itemIconList.find(pl.itemId);
				if (foundItem != itemIconList.end())
				{
					sl->SetItemIcon(&(foundItem->second));
					sl->SetItemId(pl.itemId);
					break;
				}
			}
			else
			{
				sl->SetItemIcon(nullptr);
				sl->SetItemId(ItemId::none);
			}
		}
	}
}

void QuickInventory::ItemIconSetUp()
{
	AllItemTable* allItem = DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem);
	std::unordered_map<ItemId, ItemInfo>& item = allItem->table;
	for (auto& i : item)
	{
		itemIconList.insert({ i.first, SpriteGo(i.second.resource, i.second.name_e, i.second.nickName) });
	}

	for (auto& it : itemIconList)
	{
		it.second.Reset();
		it.second.colliderOnOff = false;
		it.second.SetOrigin(Origins::MC);
		it.second.SetScale(4.5f, 4.5f);
	}
}

void QuickInventory::ItemIndexUpdate()
{
	for (tagItemInfo& pl : *playerItemList)
	{
		for (Slot* sl : quickslots)
		{
			if (pl.itemId == sl->GetItemId())
			{
				pl.index = sl->slotIndex;
				continue;
			}
		}
	}
}

