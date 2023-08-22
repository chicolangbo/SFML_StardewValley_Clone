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

void Player2::Init()
{
	SpriteGo::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Idle-up.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Idle-side.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Move-side.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Move-up.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Move.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Tool.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Tool-side.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Tool-up.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Attack.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Attack-side.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Attack-up.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Water-up.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Water-side.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/player_Water.csv"));

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

	//axe = (Axe*)SCENE_MGR.GetCurrScene()->AddGo(new Axe());
	axe.Init();
	pickax.Init();
	hoe.Init();
	scythe.Init();
	watering.Init(); 

	hitBox.setSize({ 20.f,20.f });
	hitBox.setFillColor(sf::Color::Green);

}

void Player2::Reset()
{
	SpriteGo::Reset();
	animation.Play("Idle");
	
	SetPosition({ 0, 0 });
	SetFlipX(false);

	axe.Reset();
	pickax.Reset();
	hoe.Reset();
	scythe.Reset();
	watering.Reset();

	currentClipInfo = clipInfos[6];

	playerDie = false;
	one = true;
	energy = maxEnergy;

	collider.setSize({ sprite.getGlobalBounds().width, sprite.getGlobalBounds().height });
	collider.setScale({ 0.3, 0.3 });
	SetOrigin(origin);

	playerItemList.push_back({ ItemId::ax, 1, 0 });
	playerItemList.push_back({ ItemId::homi, 1, 1 });
	playerItemList.push_back({ ItemId::hook, 1, 2 });
	playerItemList.push_back({ ItemId::pick, 1, 3 });
	playerItemList.push_back({ ItemId::waterCan, 1, 4 });
}

void Player2::Update(float dt)
{
	SpriteGo::Update(dt);

	hitBox.setPosition(GetPosition());
	
	sf::Vector2f playerPos = GetPosition();

	if (!playerDie)
	{
		direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
		direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);

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
			auto min = std::min_element(clipInfos.begin(), clipInfos.end(),
				[this](const ClipInfo& lhs, const ClipInfo& rhs) {
					return Utils::Distance(lhs.point, direction) < Utils::Distance(rhs.point, direction);
				});
			currentClipInfo = *min;
		}
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

		if (INPUT_MGR.GetKeyDown(sf::Keyboard::P)) 
		{
			energy = 0;
		}

		if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			switch (item)
			{
			case ItemId::hook:
				if (animation.GetCurrentClipId() == "Idle" || animation.GetCurrentClipId() == "Move")
				{
					animation.Play("Attack");
					scythe.SetFlipX(true);
					scythe.PlayAnimation("ScytheFront");
				}
				else if (animation.GetCurrentClipId() == "IdleSide" || animation.GetCurrentClipId() == "MoveSide")
				{
					animation.Play("AttackSide");
					if (filpX)
					{
						scythe.SetFlipX(true);
						scythe.PlayAnimation("ScytheSide");
					}
					else
					{
						scythe.SetFlipX(false);
						scythe.PlayAnimation("ScytheSide");

					}
				}
				else if (animation.GetCurrentClipId() == "IdleUp" || animation.GetCurrentClipId() == "MoveUp")
				{
					animation.Play("AttackUp");
					scythe.SetFlipX(true);
					scythe.PlayAnimation("ScytheBack");
				}
				energy -= 2;
				playingAnimation = true;
				break;

			case ItemId::ax:
				if (animation.GetCurrentClipId() == "Idle" || animation.GetCurrentClipId() == "Move")
				{
					animation.Play("Tool");
					axe.SetFlipX(true);
					axe.PlayAnimation("AxeFront");
				}
				else if (animation.GetCurrentClipId() == "IdleSide" || animation.GetCurrentClipId() == "MoveSide")
				{
					animation.Play("ToolSide");
					if (filpX)
					{
						axe.SetFlipX(true);
						axe.PlayAnimation("AxeSide");
					}
					else
					{
						axe.SetFlipX(false);
						axe.PlayAnimation("AxeSide");

					}
				}
				else if (animation.GetCurrentClipId() == "IdleUp" || animation.GetCurrentClipId() == "MoveUp")
				{
					animation.Play("ToolUp");
					axe.SetFlipX(true);
					axe.PlayAnimation("AxeBack");
				}
				energy -= 2;
				playingAnimation = true;
				break;
			case ItemId::pick:
				if (animation.GetCurrentClipId() == "Idle" || animation.GetCurrentClipId() == "Move")
				{
					animation.Play("Tool");
					pickax.SetFlipX(true);
					pickax.PlayAnimation("PickaxFront");
				}
				else if (animation.GetCurrentClipId() == "IdleSide" || animation.GetCurrentClipId() == "MoveSide")
				{
					animation.Play("ToolSide");
					if (filpX)
					{
						pickax.SetFlipX(true);
						pickax.PlayAnimation("PickaxSide");
					}
					else
					{
						pickax.SetFlipX(false);
						pickax.PlayAnimation("PickaxSide");
					}
				}
				else if (animation.GetCurrentClipId() == "IdleUp" || animation.GetCurrentClipId() == "MoveUp")
				{
					animation.Play("ToolUp");
					pickax.SetFlipX(true);
					pickax.PlayAnimation("PickaxBack");
				}
				energy -= 2;
				playingAnimation = true;
				break;

			case ItemId::homi:
				if (animation.GetCurrentClipId() == "Idle" || animation.GetCurrentClipId() == "Move")
				{
					animation.Play("Tool");
					hoe.SetFlipX(true);
					hoe.PlayAnimation("HoeFront");
				}
				else if (animation.GetCurrentClipId() == "IdleSide" || animation.GetCurrentClipId() == "MoveSide")
				{
					animation.Play("ToolSide");
					if (filpX)
					{
						hoe.SetFlipX(true);
						hoe.PlayAnimation("HoeSide");
					}
					else
					{
						hoe.SetFlipX(false);
						hoe.PlayAnimation("HoeSide");
					}
				}
				else if (animation.GetCurrentClipId() == "IdleUp" || animation.GetCurrentClipId() == "MoveUp")
				{
					animation.Play("ToolUp");
					hoe.SetFlipX(true);
					hoe.PlayAnimation("HoeBack");
				}
				energy -= 2;
				playingAnimation = true;
				break;

			case ItemId::waterCan:
				SetOrigin(Origins::BC);
				if (animation.GetCurrentClipId() == "Idle" || animation.GetCurrentClipId() == "Move")
				{
					animation.Play("Water");
					watering.SetFlipX(true);
					watering.PlayAnimation("WateringFront");
				}
				else if (animation.GetCurrentClipId() == "IdleSide" || animation.GetCurrentClipId() == "MoveSide")
				{
					animation.Play("WaterSide");

					if (filpX)
					{
						watering.SetFlipX(true);
						watering.PlayAnimation("WateringSide");
					}
					else
					{
						watering.SetFlipX(false);
						watering.PlayAnimation("WateringSide");
					}
				}
				else if (animation.GetCurrentClipId() == "IdleUp" || animation.GetCurrentClipId() == "MoveUp")
				{
					animation.Play("WaterUp");
					watering.SetFlipX(true);
					watering.PlayAnimation("WateringBack");
				}
				energy -= 2;
				playingAnimation = true;
				break;
			
			case ItemId::none:
				SetOrigin(Origins::BC);
				break;
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
	window.draw(hitBox);
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

void Player2::AddRootingItem() // 자석화 해야 함
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
			item->SetActive(false);
			AddPlayerItem(item->GetRootingItemId());
		}
	}
}

void Player2::AddPlayerItem(ItemId id)
{
	inven->IconUpdate();
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

ItemId Player2::GetEquipItem()
{
	return item;
}

