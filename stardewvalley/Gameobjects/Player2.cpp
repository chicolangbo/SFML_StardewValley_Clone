#include "stdafx.h"
#include "Player2.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"

void Player2::Init()
{
	SpriteGo::Init();
	std::string textureId = "graphics/farmer_base.png";

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
	std::cout << playerPos.x << " " << playerPos.y << std::endl;
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
		item = 2;
	}

	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		switch (item)
		{
		case 1:
			animation.Play("Attack");
			energy -= 2;
			playingAnimation = true;
			break;
		case 2:
			animation.Play("Tool");
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
}

void Player2::Draw(sf::RenderWindow& window)
{
	// 김민지, 230809, 콜라이더용 추가
	SpriteGo::Draw(window);
	//
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