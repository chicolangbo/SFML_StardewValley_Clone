#include "stdafx.h"
#include "Player2.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "SceneGame.h"
#include "Scene.h"
#include "Axe.h"
#include "RootingItem.h"
#include "AllItemTable.h"
#include "DataTableMgr.h"
#include "Inventory.h"
#include "Slot.h"
#include "SceneTitle.h"

void Player2::Init()
{
	SpriteGo::Init();
	
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Idle-up.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Idle-side.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Move-side.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Move-up.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Move.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_MoveItem.csv"));//아이템 들고 이동
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_MoveItem-side.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_MoveItem-up.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_IdleItem.csv"));//아이템 들고 서있음
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_IdleItem-Side.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_IdleItem-Up.csv"));
	

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Tool.csv")); 
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Tool-side.csv")); 
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Tool-up.csv")); 

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Attack.csv")); 
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Attack-side.csv")); 
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Attack-up.csv")); 

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Water-up.csv")); 
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Water-side.csv")); 
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Water.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_harvest.csv"));//작물 뽑을때 Hatvest
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_harvest-side.csv")); //HarvestSide
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_harvest-up.csv"));  //HarvestUp

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Die.csv"));

	animation.SetTarget(&sprite);
	sprite.setScale(4.5f, 4.5f);
	SetOrigin(Origins::BC);

	clipInfos.push_back({ "IdleSide", "MoveSide", false, Utils::Normalize({-1.f, -1.f})});
	clipInfos.push_back({ "IdleUp", "MoveUp", true, {0.f, -1.f} });
	clipInfos.push_back({ "IdleSide", "MoveSide", true, Utils::Normalize({ 1.f, -1.f }) });

	clipInfos.push_back({ "IdleSide", "MoveSide", false, {-1.f, 0.f} });
	clipInfos.push_back({ "IdleSide", "MoveSide", true, {1.f, 0.f} });

	clipInfos.push_back({ "IdleSide", "MoveSide", false, Utils::Normalize({ -1.f, 1.f }) });
	clipInfos.push_back({ "Idle", "Move", true,{0.f, 1.f} });
	clipInfos.push_back({ "IdleSide", "MoveSide", true, Utils::Normalize({ 1.f, 1.f }) });

	

	clipInfosItem.push_back({ "IdleItemSide", "MoveItemSide", false, Utils::Normalize({-1.f, -1.f}) });
	clipInfosItem.push_back({ "IdleItemUp", "MoveItemUp", true, {0.f, -1.f} });
	clipInfosItem.push_back({ "IdleItemSide", "MoveItemSide", true, Utils::Normalize({ 1.f, -1.f }) });

	clipInfosItem.push_back({ "IdleItemSide", "MoveItemSide", false, {-1.f, 0.f} });
	clipInfosItem.push_back({ "IdleItemSide", "MoveItemSide", true, {1.f, 0.f} });

	clipInfosItem.push_back({ "IdleItemSide", "MoveItemSide", false, Utils::Normalize({ -1.f, 1.f }) });
	clipInfosItem.push_back({ "IdleItem", "MoveItem", true,{0.f, 1.f} });
	clipInfosItem.push_back({ "IdleItemSide", "MoveItemSide", true, Utils::Normalize({ 1.f, 1.f }) });

	axe.Init();
	pickax.Init();
	hoe.Init();
	scythe.Init();
	watering.Init(); 
	ItemIconSetUp();
}

void Player2::Reset()
{
	SpriteGo::Reset();
	animation.Play("Idle");
	
	SetFlipX(false);

	axe.Reset();
	pickax.Reset();
	hoe.Reset();
	scythe.Reset();
	watering.Reset();

	currentClipInfo = clipInfos[6];  
	currentClipInfoItem = clipInfosItem[6]; 

	playerDie = false;
	one = true;

	if (!load) // NEW GAME
	{
		energy = maxEnergy;
		money = 500;
		tempMoney = 0;
		totalEarningsInt = 500;
		playerItemList.clear();
		playerItemList.push_back({ ItemId::ax, 1, 0 });
		playerItemList.push_back({ ItemId::homi, 1, 1 });
		playerItemList.push_back({ ItemId::hook, 1, 2 });
		playerItemList.push_back({ ItemId::pick, 1, 3 });
		playerItemList.push_back({ ItemId::waterCan, 1, 4 });
		playerItemList.push_back({ ItemId::parsnipSeed, 5, 5 });
		playerItemList.push_back({ ItemId::potatoSeed, 5, 6 });
		playerItemList.push_back({ ItemId::coliSeed, 5, 7 });
		playerItemList.push_back({ ItemId::branch, 50, 8 });
		playerItemList.push_back({ ItemId::coal, 1, 9 });
		playerItemList.push_back({ ItemId::fiver, 20, 10 });
		item = ItemId::none;
	}

	collider.setSize({ sprite.getGlobalBounds().width, sprite.getGlobalBounds().height });
	collider.setScale({ 0.5f, 0.15f });
	SetOrigin(origin);

	handitem = nullptr;
	
}

void Player2::Update(float dt)
{
	SpriteGo::Update(dt);

	//hitBox.setPosition(GetPosition());
	

	sf::Vector2f playerPos = GetPosition();

	if (item != ItemId::pick && item != ItemId::ax && item != ItemId::homi && item != ItemId::waterCan && item != ItemId::hook && item != ItemId::none)
	{
		auto it = itemIconList.find(item);
		if (it != itemIconList.end())
		{
			handitem = new SpriteGo(it->second.textureId, it->second.name, it->second.nickName);
			handitem->Reset();
			handitem->SetScale({ 4.5f,4.5f });
			handitem->SetOrigin(Origins::MC);
			handitem->SetPosition(playerPos.x, playerPos.y - 130.f);
		}
	}
	else
	{
		delete handitem;
		handitem = nullptr; 
	}


	//std::cout << (int)item << std::endl;
	if (!playerDie)
	{
		if (!playingAnimation)
		{
			direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
			direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);
		}
		float magnitude = Utils::Magnitude(direction);
		if (magnitude > 1.f)
		{
			direction /= magnitude;
		}

		//sf::Vector2f newPosition = position + direction * dt * speed;
		//collider.setPosition(newPosition);

		playerBound = collider.getGlobalBounds(); 
		for (int i = 0; i < wallBounds.size(); ++i)
		{
			if (collider.getGlobalBounds().intersects(wallBounds[i]))
			{
				if (position.x < wallBoundsLT[i].x)
				{
					if (INPUT_MGR.GetKey(sf::Keyboard::A))
					{
						direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
					}
					else
					{
						direction.x = 0;
					}
				}
				else if (position.x > wallBoundsRB[i].x)
				{
					if (INPUT_MGR.GetKey(sf::Keyboard::D))
					{
						direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal); 
					}
					else
					{
						direction.x = 0;
					}
				}
				else if (position.y < wallBoundsRB[i].y)
				{
					if (INPUT_MGR.GetKey(sf::Keyboard::W))
					{
						direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical); 
					}
					else
					{
						direction.y = 0;
					}
				}
				else if (position.y > wallBoundsRB[i].y)
				{
					if (INPUT_MGR.GetKey(sf::Keyboard::S))
					{
						direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);
					}
					else
					{
						direction.y = 0;
					}
				}
			}
		}
		position += direction * speed * dt;
		SetPosition(position);


		//도구 사용
		axe.Update(dt);
		axe.SetPosition(position);
		axe.SetOrigins();

		pickax.Update(dt);
		pickax.SetPosition(position);
		pickax.SetOrigins();

		hoe.Update(dt);
		hoe.SetPosition(position);
		hoe.SetOrigins();

		scythe.Update(dt);
		scythe.SetPosition(position);
		scythe.SetOrigins();

		watering.Update(dt);
		watering.SetPosition(position);
		watering.SetOrigins();


		if ((direction.x != 0.f || direction.y != 0.f))
		{
			if (item == ItemId::none || item == ItemId::pick || item == ItemId::ax || item == ItemId::homi || item == ItemId::waterCan || item == ItemId::hook)
			{
				auto min = std::min_element(clipInfos.begin(), clipInfos.end(),
					[this](const ClipInfo& lhs, const ClipInfo& rhs) {
						return Utils::Distance(lhs.point, direction) < Utils::Distance(rhs.point, direction);
					});
				currentClipInfo = *min;
			}
			else
			{
				auto mins = std::min_element(clipInfosItem.begin(), clipInfosItem.end(),
					[this](const HandOnItem& lhs, const HandOnItem& rhs) {
						return Utils::Distance(lhs.point, direction) < Utils::Distance(rhs.point, direction);
					});
				currentClipInfoItem = *mins;
			}
		}
		//아이템 들고있는것에따라 모션
		{
			if (item == ItemId::none || item == ItemId::pick || item == ItemId::ax || item == ItemId::homi || item == ItemId::waterCan || item == ItemId::hook)
			{
				std::string clipId = magnitude == 0.f ? currentClipInfo.idle : currentClipInfo.move;
				if (GetFlipX() != currentClipInfo.flipX)
				{
					SetFlipX(currentClipInfo.flipX);
				}
				if (!playingAnimation)
				{
					if (animation.GetCurrentClipId() != clipId) 
					{
						animation.Play(clipId); 
					}
				}
			}
			else
			{
				std::string clipId = magnitude == 0.f ? currentClipInfoItem.idleItem : currentClipInfoItem.moveItem;
				if (GetFlipX() != currentClipInfoItem.flipX)
				{
					SetFlipX(currentClipInfoItem.flipX);
				}
				if (!playingAnimation)
				{
					if (animation.GetCurrentClipId() != clipId)
					{
						animation.Play(clipId);
					}
				}
			}
		}
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::P)) 
		{
			energy = 0;
		}

		if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			if (!playingAnimation)
			{
				switch (item)
				{
				case ItemId::hook:
					if (playerTileIndex.y < mouseTileIndex.y)
					{
						if (harvest)
						{
							animation.Play("Harvest");
							harvest = false;
						}
						else
						{
							animation.Play("Attack");
							scythe.SetFlipX(true);
							scythe.PlayAnimation("ScytheFront");
						}
					}
					else if (playerTileIndex.x < mouseTileIndex.x || playerTileIndex.x > mouseTileIndex.x)
					{

						if (playerTileIndex.x < mouseTileIndex.x)
						{
							if (harvest)
							{
								SetScale(4.5f, 4.5f);
								animation.Play("HarvestSide"); 
							}
							else
							{
								scythe.SetFlipX(true);
								scythe.PlayAnimation("ScytheSide");
								SetScale(4.5f, 4.5f);
								animation.Play("AttackSide");
							}
						}
						if (playerTileIndex.x > mouseTileIndex.x)
						{
							if (harvest)
							{
								SetScale(-4.5f, 4.5f); 
								animation.Play("HarvestSide");
							}
							else
							{
								scythe.SetFlipX(false);
								scythe.PlayAnimation("ScytheSide");
								SetScale(-4.5f, 4.5f);
								animation.Play("AttackSide");
							}
						}
					}
					else if (playerTileIndex.y > mouseTileIndex.y)
					{
						if (harvest)
						{
							animation.Play("HarvestUp");
						}
						else 
						{
							animation.Play("AttackUp");
							scythe.SetFlipX(true);
							scythe.PlayAnimation("ScytheBack");
						}
						
					}
					energy -= 2;
					playingAnimation = true;
					direction = { 0,0 };
					break;

				case ItemId::ax:
					if (playerTileIndex.y < mouseTileIndex.y)
					{
						if (harvest)
						{
							animation.Play("Harvest");
							harvest = false;
						}
						else
						{
							animation.Play("Tool");
							axe.SetFlipX(true);
							axe.PlayAnimation("AxeFront");
						}
					}
					else if (playerTileIndex.x < mouseTileIndex.x || playerTileIndex.x > mouseTileIndex.x)
					{

						if (playerTileIndex.x < mouseTileIndex.x)
						{
							if (harvest)
							{
								SetScale(4.5f, 4.5f);
								animation.Play("HarvestSide");
								harvest = false;
							}
							else
							{
								axe.SetFlipX(true);
								axe.PlayAnimation("AxeSide");
								SetScale(4.5f, 4.5f);
								animation.Play("ToolSide");
							}
						}
						if (playerTileIndex.x > mouseTileIndex.x)
						{
							if (harvest)
							{
								SetScale(-4.5f, 4.5f);
								animation.Play("HarvestSide");
								harvest = false;
							}
							else
							{
								axe.SetFlipX(false);
								axe.PlayAnimation("AxeSide");
								SetScale(-4.5f, 4.5f);
								animation.Play("ToolSide");
							}
						}
					}
					else if (playerTileIndex.y > mouseTileIndex.y)
					{
						if (harvest)
						{
							animation.Play("HarvestUp");
							harvest = false;
						}
						else
						{
							animation.Play("ToolUp");
							axe.SetFlipX(true);
							axe.PlayAnimation("AxeBack");
						}
					}
					energy -= 2;
					playingAnimation = true;
					direction = { 0,0 };
					break;
				case ItemId::pick:
					if (playerTileIndex.y < mouseTileIndex.y)
					{
						if (harvest)
						{
							animation.Play("Harvest");
							harvest = false;
						}
						else
						{
							animation.Play("Tool");
							pickax.SetFlipX(true);
							pickax.PlayAnimation("PickaxFront");
						}
						
					}
					else if (playerTileIndex.x < mouseTileIndex.x || playerTileIndex.x > mouseTileIndex.x)
					{

						if (playerTileIndex.x < mouseTileIndex.x)
						{
							if (harvest)
							{
								SetScale(4.5f, 4.5f);
								animation.Play("HarvestSide");
								harvest = false;
							}
							else
							{
								pickax.SetFlipX(true);
								pickax.PlayAnimation("PickaxSide");
								SetScale(4.5f, 4.5f);
								animation.Play("ToolSide");
							}
						}
						if (playerTileIndex.x > mouseTileIndex.x)
						{
							if (harvest)
							{
								SetScale(-4.5f, 4.5f);
								animation.Play("HarvestSide");
								harvest = false;
							}
							else
							{
								pickax.SetFlipX(false);
								pickax.PlayAnimation("PickaxSide");
								SetScale(-4.5f, 4.5f);
								animation.Play("ToolSide");
							}
						}
					}
					else if (playerTileIndex.y > mouseTileIndex.y)
					{
						if (harvest)
						{
							animation.Play("HarvestUp");
							harvest = false;
						}
						else
						{
							animation.Play("ToolUp");
							pickax.SetFlipX(true);
							pickax.PlayAnimation("PickaxBack");
						}
					}
					energy -= 2;
					playingAnimation = true;
					direction = { 0,0 };
					break;

				case ItemId::homi:
					if (playerTileIndex.y < mouseTileIndex.y)
					{
						if (harvest)
						{
							animation.Play("Harvest");
							harvest = false;
						}
						else
						{
							animation.Play("Tool");
							hoe.SetFlipX(true);
							hoe.PlayAnimation("HoeFront");
						}
					}
					else if (playerTileIndex.x < mouseTileIndex.x || playerTileIndex.x > mouseTileIndex.x)
					{

						if (playerTileIndex.x < mouseTileIndex.x)
						{
							if (harvest)
							{
								SetScale(4.5f, 4.5f);
								animation.Play("HarvestSide");
								harvest = false;
							}
							else
							{
								hoe.SetFlipX(true);
								hoe.PlayAnimation("HoeSide");
								SetScale(4.5f, 4.5f);
								animation.Play("ToolSide");
							}
						}
						if (playerTileIndex.x > mouseTileIndex.x)
						{
							if (harvest)
							{
								SetScale(-4.5f, 4.5f);
								animation.Play("HarvestSide");
								harvest = false;
							}
							else
							{
								hoe.SetFlipX(false);
								hoe.PlayAnimation("HoeSide");
								SetScale(-4.5f, 4.5f);
								animation.Play("ToolSide");
							}
						}
					}
					else if (playerTileIndex.y > mouseTileIndex.y)
					{
						if (harvest)
						{
							animation.Play("HarvestUp");
							harvest = false;
						}
						else
						{
							animation.Play("ToolUp");
							hoe.SetFlipX(true);
							hoe.PlayAnimation("HoeBack");
						}
					}
					energy -= 2;
					playingAnimation = true;
					direction = { 0,0 };
					break;

				case ItemId::waterCan:
					SetOrigin(Origins::BC);
					if (playerTileIndex.y < mouseTileIndex.y)
					{
						if (harvest)
						{
							animation.Play("Harvest");
							harvest = false;
						}
					}
					else if (playerTileIndex.x < mouseTileIndex.x || playerTileIndex.x > mouseTileIndex.x)
					{
						if (playerTileIndex.x < mouseTileIndex.x)
						{
							if (harvest)
							{
								SetScale(4.5f, 4.5f);
								animation.Play("HarvestSide");
								harvest = false;
							}
						}
						if (playerTileIndex.x > mouseTileIndex.x)
						{
							if (harvest)
							{
								SetScale(-4.5f, 4.5f);
								animation.Play("HarvestSide");
								harvest = false;
							}
						}
					}
					else if (playerTileIndex.y > mouseTileIndex.y)
					{
						if (harvest)
						{
							animation.Play("HarvestUp");
							harvest = false;
						}
					}
					energy -= 2;
					playingAnimation = true;
					direction = { 0,0 };
					break;

				default:
					SetOrigin(Origins::BC);
					if (playerTileIndex.y < mouseTileIndex.y)
					{
						if (harvest)
						{
							animation.Play("Harvest");
							harvest = false;
						}
					}
					else if (playerTileIndex.x < mouseTileIndex.x || playerTileIndex.x > mouseTileIndex.x)
					{
						if (playerTileIndex.x < mouseTileIndex.x)
						{
							if (harvest)
							{
								SetScale(4.5f, 4.5f);
								animation.Play("HarvestSide");
								harvest = false;
							}
						}
						if (playerTileIndex.x > mouseTileIndex.x)
						{
							if (harvest)
							{
								SetScale(-4.5f, 4.5f);
								animation.Play("HarvestSide");
								harvest = false;
							}
						}
					}
					else if (playerTileIndex.y > mouseTileIndex.y)
					{
						if (harvest)
						{
							animation.Play("HarvestUp");
							harvest = false;
						}
					}
					playingAnimation = true;
					direction = { 0,0 };
					break;
				}
			}
		}
	}


    else if (playerDie&&one)
	{
		animation.Play("Die");
		one = false;
	}
	
	if (energy == 0)
	{
		playerDie = true;
	}

	if (animation.GetTotalFrame() - animation.GetCurrentFrame() == 1)
	{
		playingAnimation = false;
		//harvest = false;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::LControl))
	{
		Reset(); 
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Add))
	{
		money += 100;
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Subtract))
	{
		money -= 100;
	}
	animation.Update(dt);

	// 아이템 관련
	AddRootingItem();
		
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num8))
	{
		int a = 0;
		for (auto& i : playerItemList)
		{
			std::cout << "============ pushnum: " << a << "============" << std::endl;
			std::cout << "count: "<< i.count << std::endl;
			std::cout << "index: "<< i.index << std::endl;
			a++;
		}
	}

	// MONEY TEST CODE
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::P))
	{
		tempMoney = 300;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::O))
	{
		tempMoney = -300;
	}
	MoneyUpdate();
	//타일맵 베이스
}

void Player2::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(axe.sprite); 
	window.draw(pickax.sprite); 
	window.draw(hoe.sprite);
	window.draw(scythe.sprite);
	window.draw(watering.sprite);
	if (handitem!=nullptr && !playingAnimation) 
	{
		window.draw(handitem->sprite);
	}
	//handitem->Draw(window);
}

bool Player2::GetFlipX() const
{
	return filpX;
}

void Player2::SetFlipX(bool filp)
{
	filpX = filp;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !filpX ? -abs(scale.x) : abs(scale.x);
	sprite.setScale(scale);
}

void Player2::SetWallBounds(const sf::FloatRect& bounds)
{
	wallBounds.push_back(bounds); 
	wallBoundsLT.push_back({ bounds.left, bounds.top });
	wallBoundsRB.push_back({ bounds.left + bounds.width, bounds.top + bounds.height });

}

void Player2::SetCollider(const sf::FloatRect& coll)
{
	playerBound = coll;
}

void Player2::ClearWalls()
{
	wallBounds.clear();
	wallBoundsLT.clear();
	wallBoundsRB.clear(); 
}

void Player2::LoadData(std::list<tagItemInfo> loadI, int loadTM, int loadM, int loadE)
{
	playerItemList.clear();
	playerItemList = loadI;
	totalEarningsInt = loadTM;
	money = loadM;
	energy = loadE;
	item = ItemId::none;
	load = true;
}

void Player2::AddRootingItem() // 자석화 해야 함 // 했음
{
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrScene());
	Inventory* inven = (Inventory*)scene->FindGo("inven");
	int capacity = inven->GetItemCapacity();

	if (playerItemList.size() >= capacity || rootingItemList->empty())
	{
		return;
	}

	for (auto item : *rootingItemList)
	{
		if (sprite.getGlobalBounds().intersects(item->sprite.getGlobalBounds()) && item->GetActive())
		{
			if (item->PongEnd())
			{
				item->SetActive(false);
				AddPlayerItem(item->GetRootingItemId());
			}
			//check = false;
		}
	}
}

void Player2::AddPlayerItem(ItemId id)
{
	bool found = false;

	for (auto& playerItem : playerItemList)
	{
		if (playerItem.itemId == id)
		{
			playerItem.count++;
			found = true;
			break;
		}
	}
	if (!found)
	{
		inven->IconUpdate();
		int index = 0;
		for (auto slot : *inven->GetSlot())
		{
			if (slot->IsItemIconEmpty())
			{
				index = slot->slotIndex;
				break;
			}
		}
		playerItemList.push_back({ id,1,index });
	}
	inven->IconUpdate();
}

bool Player2::RemovePlayerItem(ItemId id)
{
	bool found = false;
	auto it = playerItemList.begin();
	while (it != playerItemList.end())
	{
		if (it->itemId == id)
		{
			if (it->count > 1)
			{
				it->count--;
				return found = true;
				break;
			}
			else if (it->count <= 1)
			{
				it = playerItemList.erase(it); // erase() 함수를 사용하여 현재 요소를 삭제하고 다음 요소로 이동
				return found = true;
				break;
			}
		}
		++it; // 다음 요소로 이동
	}
	return found;
}

void Player2::MoneyUpdate()
{
	if (tempMoney != 0)
	{
		money += tempMoney;
		if (tempMoney >= 0)
		{
			totalEarningsInt += tempMoney;
		}
	}
	tempMoney = 0;
}

int Player2::GetItemCount()
{
	for (auto& i : playerItemList)
	{
		if (i.itemId == item)
		{
			return i.count;
		}
	}
	cout << "ERR: Don't have Item" << endl;
	return -1;
}

void Player2::ItemIconSetUp()
{
	AllItemTable* allItem = DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem);
	std::unordered_map<ItemId, ItemInfo>& item = allItem->table;
	for (auto& i : item)
	{
		//SpriteGo temp(i.second.resource, i.second.name_e, i.second.nickName);
		itemIconList.insert({ i.first,
			{ i.second.resource, i.second.name_e, i.second.nickName},
			}); 
	}

	/*for (auto& it : itemIconList)
	{
		it.second.Reset(); 
		it.second.colliderOnOff = false;
		it.second.SetOrigin(Origins::MC);
		it.second.SetScale(4.5f, 4.5f);
	}*/
}
