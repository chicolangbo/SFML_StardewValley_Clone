#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "DataTableMgr.h"
#include "ClipTable.h"
#include "ResourceMgr.h"

void Player::SetWallBounds(const sf::FloatRect& bounds)
{
	wallBounds = bounds;

	wallBoundsLT = { wallBounds.left, wallBounds.top };
	wallBoundsRB = { wallBounds.left + wallBounds.width, wallBounds.top + wallBounds.height };
}

bool Player::GetFlipX() const
{
	return flipX;
}

void Player::SetFlipX(bool flip)
{
	flipX = flip;
	if (flip)
	{
		sprite.setScale(-1.f, 1.f);
	}
	else
	{
		sprite.setScale(1.f, 1.f);
	}
}

void Player::Init()
{
	////파싱으로 변경 필요
	//std::string textureId = "graphics/RubySheet.png";
	//
	///*----Idle----*/
	////idle front
	//{
	//	AnimationClip clip;
	//	clip.id = "IdleFront";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	//
	//	//sf::IntRect coord(768, 256, 256, 256); //start 이미지, 하나의 크키가 256*256 
	//	clip.frames.push_back({ textureId, sf::IntRect(256, 768, 256, 256) });
	//	clip.frames.push_back({ textureId, sf::IntRect(256, 1024, 256, 256) });
	//	animation.AddClip(clip);
	//}
	////idle left
	//{
	//	AnimationClip clip;
	//	clip.id = "IdleLeft";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	//
	//	//sf::IntRect coord(768, 256, 256, 256); //start 이미지, 하나의 크키가 256*256 
	//	clip.frames.push_back({ textureId, sf::IntRect(0, 768, 256, 256) });
	//	clip.frames.push_back({ textureId, sf::IntRect(0, 1024, 256, 256) });
	//	animation.AddClip(clip);
	//}
	////idle Back
	//{
	//	AnimationClip clip;
	//	clip.id = "IdleBack";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	//
	//	//sf::IntRect coord(768, 256, 256, 256); //start 이미지, 하나의 크키가 256*256 
	//	clip.frames.push_back({ textureId, sf::IntRect(512, 768, 256, 256) });
	//	clip.frames.push_back({ textureId, sf::IntRect(512, 1024, 256, 256) });
	//	animation.AddClip(clip);
	//}
	///*----Move----*/
	////move left
	//{
	//	AnimationClip clip;
	//	clip.id = "MoveLeft";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	//
	//	sf::IntRect coord(0, 0, 256, 256); //start 이미지, 하나의 크키가 120x120 
	//	for (int i = 0; i < 4; i++)
	//	{
	//		clip.frames.push_back({ textureId, coord });
	//		coord.left += coord.width;
	//	}
	//	animation.AddClip(clip);
	//}
	//
	////move back
	//{
	//	AnimationClip clip;
	//	clip.id = "MoveBack";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	//
	//	sf::IntRect coord(0, 256, 256, 256); //start 이미지, 하나의 크키가 120x120 
	//	for (int i = 0; i < 4; i++)
	//	{
	//		clip.frames.push_back({ textureId, coord });
	//		coord.left += coord.width;
	//	}
	//	animation.AddClip(clip);
	//}
	//
	////move front
	//{
	//	AnimationClip clip;
	//	clip.id = "MoveFront";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;
	//
	//	sf::IntRect coord(0, 512, 256, 256); //start 이미지, 하나의 크키가 120x120 
	//	for (int i = 0; i < 4; i++)
	//	{
	//		clip.frames.push_back({ textureId, coord });
	//		coord.left += coord.width;
	//	}
	//	animation.AddClip(clip);
	//}

	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/IdleBack.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/IdleFront.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/IdleLeft.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/MoveLeft.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/MoveBack.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/MoveFront.csv");

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/IdleBack.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/IdleFront.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/IdleLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/MoveLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/MoveBack.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/MoveFront.csv"));

	animation.SetTarget(&sprite);
	SetOrigin(Origins::BC);
}

void Player::Reset()
{
	//SpriteGo::Reset();

	animation.Play("IdleFront");
	SetOrigin(origin);
	SetPosition(0, 0);
	SetFlipX(false);

	//animation.Play("Idle");
	//SetOrigin(origin);
	//SetPosition(0, 0);
	//SetFlipX(false);
}

void Player::Update(float dt)
{
	//SpriteGo::Update(dt);
	//animation.Update(dt);
	//float h = INPUT_MGR.GetAxis(Axis::Horizontal);
	////플립
	//if (h != 0.f)
	//{
	//	bool flip = h < 0.f;
	//	if (GetFlipX() != flip)
	//	{
	//		SetFlipX(flip);
	//	}
	//}
	////점프
	//if (isGround && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	//{
	//	velocity.y += JumpForce;
	//	animation.Play("Jump");
	//	isGround = false;
	//}
	//
	////이동
	//velocity.x = h * speed;
	//velocity.y += gravity * dt;
	//position += velocity * dt;
	//
	////바닥 충돌 처리
	//if (position.y > 0.f)
	//{
	//	isGround = true;
	//	position.y = 0.f;
	//	velocity.y = 0.f;
	//}
	//SetPosition(position);
	//
	//if (animation.GetCurrentClipId() == "Idle")
	//{
	//	if (isGround && h != 0.f)
	//	{
	//		animation.Play("Move");
	//	}
	//}
	//else if (animation.GetCurrentClipId() == "Move")
	//{
	//	if (isGround && h == 0.f)
	//	{
	//		animation.Play("Idle");
	//	}
	//}
	//else if (animation.GetCurrentClipId() == "Jump")
	//{
	//	if (isGround)
	//	{
	//		animation.Play((h == 0.f) ? "Idle" : "Move");
	//	}
	//}
	SpriteGo::Update(dt);
	animation.Update(dt);
	float h = INPUT_MGR.GetAxis(Axis::Horizontal);
	float v = INPUT_MGR.GetAxis(Axis::Vertical);
	//플립
	if (h != 0.f)
	{
		bool flip = h > 0.f;
		if (GetFlipX() != flip)
		{
			SetFlipX(flip);
		}
	}

	//이동
	velocity.x = h * speed;
	velocity.y = v * speed;
	position += velocity * dt;

	if (!wallBounds.contains(position))
	{
		position = Utils::Clamp(position, wallBoundsLT, wallBoundsRB);
	}

	SetPosition(position);

	//애니메이션
	if (animation.GetCurrentClipId() == "IdleFront" ||
		animation.GetCurrentClipId() == "IdleLeft" ||
		animation.GetCurrentClipId() == "IdleBack")
	{
		if (h != 0.f)
		{
			animation.Play("MoveLeft");
		}
		if (v > 0.f)
		{
			animation.Play("MoveFront");
		}
		if (v < 0.f)
		{
			animation.Play("MoveBack");
		}
	}
	else if (animation.GetCurrentClipId() == "MoveLeft")
	{
		if (h == 0.f)
		{
			animation.Play("IdleLeft");
		}
	}
	else if (animation.GetCurrentClipId() == "MoveFront")
	{
		if (v == 0.f)
		{
			animation.Play("IdleFront");
		}
	}
	else if (animation.GetCurrentClipId() == "MoveBack")
	{
		if (v == 0.f)
		{
			animation.Play("IdleBack");
		}
	}
}

