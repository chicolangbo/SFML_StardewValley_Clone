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
// 김민지, 230815, 아이템 관련 추가
#include "RootingItem.h"
#include "AllItemTable.h"
#include "DataTableMgr.h"
#include "Inventory.h"

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

	animation.SetTarget(&sprite);
	sprite.setScale(4.5f, 4.5f);
	SetOrigin(Origins::MC);


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
}

void Player2::Reset()
{
	// 김민지, 230809, 콜라이더용 추가
	SpriteGo::Reset();
	//
	animation.Play("Idle");
	// 김민지, 230809, 위치 이동
	//SetOrigin(origin);
	//
	
	SetPosition({ 0, 0 });
	SetFlipX(false);

	axe.Reset();
	pickax.Reset();

	currentClipInfo = clipInfos[6];

	// 김민지, 230809, 콜라이더용 추가
	collider.setSize({ sprite.getGlobalBounds().width, sprite.getGlobalBounds().height });
	SetOrigin(origin);
	//
}

void Player2::Update(float dt)
{
	// 김민지, 230809, 콜라이더용 추가
	SpriteGo::Update(dt);
	//

	//sf::Vector2f mousePos = INPUT_MGR.GetMousePos(); 
	//sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	//sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->WorldPosToScreen(position);
	
	sf::Vector2f playerPos = GetPosition();
	//std::cout << playerPos.x << " " << playerPos.y << std::endl;
	//이동
	direction.x = INPUT_MGR.GetAxis(Axis::Horizontal); 
	direction.y = INPUT_MGR.GetAxis(Axis::Vertical); 
	float magnitude = Utils::Magnitude(direction); 
	if (magnitude > 1.f)
	{
		direction /= magnitude;
	}
	position += direction * speed * dt;

	SetPosition(position);

	axe.Update(dt);
	axe.SetPosition(position);
	axe.SetOrigins();

	pickax.Update(dt);
	pickax.SetPosition(position);
	pickax.SetOrigins(); 

	if ((direction.x != 0.f || direction.y != 0.f)) 
	{
		auto min = std::min_element(clipInfos.begin(), clipInfos.end(), 
			[this](const ClipInfo& lhs, const ClipInfo& rhs) { 
				return Utils::Distance(lhs.point, direction) < Utils::Distance(rhs.point, direction); 
			});
		currentClipInfo = *min;
	}
	//이동이 있으면 true 없으면 false
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

	//test
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		item = 1;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	{
		item = 2;//도끼
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
	{
		item = 3;//곡괭이
	}

	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		switch (item)
		{
		case 1:
			if (animation.GetCurrentClipId() == "Idle" || animation.GetCurrentClipId() == "Move")
			{
				animation.Play("Attack");
			}
			else if (animation.GetCurrentClipId() == "IdleSide" || animation.GetCurrentClipId() == "MoveSide")
			{
				animation.Play("AttackSide");
			}
			else if (animation.GetCurrentClipId() == "IdleUp" || animation.GetCurrentClipId() == "MoveUp")
			{
				animation.Play("AttackUp");
			}
			energy -= 2;
			playingAnimation = true;
			break;
		case 2:
			if (animation.GetCurrentClipId() == "Idle" || animation.GetCurrentClipId() == "Move")
			{
				animation.Play("Tool");
				//여기다가 클립ID넘기면 실행됨
				axe.PlayAnimation("AxeFront");
			}
			else if (animation.GetCurrentClipId() == "IdleSide" || animation.GetCurrentClipId() == "MoveSide")
			{
				animation.Play("ToolSide");
				if (filpX)
				{
					//왼쪽 방향하는 애니매이션 실행
				}
				else
				{
					//오른쪽 방향
				}
			}
			else if (animation.GetCurrentClipId() == "IdleUp" || animation.GetCurrentClipId() == "MoveUp")
			{
				animation.Play("ToolUp");
				axe.PlayAnimation("AxeBack");
			}
			energy -= 2;
			playingAnimation = true;
			break;
		case 3:
			if (animation.GetCurrentClipId() == "Idle" || animation.GetCurrentClipId() == "Move")
			{
				animation.Play("Tool");
				pickax.PlayAnimation("PickaxFront");
			}
			else if (animation.GetCurrentClipId() == "IdleSide" || animation.GetCurrentClipId() == "MoveSide")
			{
				animation.Play("ToolSide");
				if (filpX)
				{
					//왼쪽 방향하는 애니매이션 실행
				}
				else
				{
					//오른쪽 방향
				}
			}
			else if (animation.GetCurrentClipId() == "IdleUp" || animation.GetCurrentClipId() == "MoveUp")
			{
				animation.Play("ToolUp");
				pickax.PlayAnimation("PickaxBack"); 
			}
			energy -= 2;
			playingAnimation = true;
			break;

		}
		

	}
	if (animation.GetTotalFrame() - animation.GetCurrentFrame() == 1)
	{
		playingAnimation = false;
	}

	animation.Update(dt);

	// 김민지,230815, 스폰되는 아이템 먹는지 체크하는 함수
	AddPlayerItem();
	//
}

void Player2::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(axe.sprite); 
	window.draw(pickax.sprite); 
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

void Player2::AddPlayerItem()
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
		if (sprite.getGlobalBounds().intersects(item->sprite.getGlobalBounds())) // 나중에 자석 형태로 바꾸기. 일단은 충돌 시 먹히는 걸로
		{
			item->SetActive(false);
			bool found = false;
			for (auto playerItem : playerItemList)
			{
				if (playerItem.itemId == item->GetRootingItemId())
				{
					playerItem.count++;
					found = true;
					break;
				}
			}
			if(!found)
			{
				int index = playerItemList.size();
				playerItemList.push_back({ item->GetRootingItemId(),1,index });
			}
		}
	}
}

