#include "stdafx.h"
#include "Player2.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"

void Player2::Init()
{
	SpriteGo::Init();
	std::string textureId = "graphics/RubySheet.png";

	////Idle
	//{
	//	AnimationClip clip;
	//	clip.id = "Idle_Side";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;

	//	clip.frames.push_back({ textureId,sf::IntRect(0,256 * 3,256,256) });
	//	clip.frames.push_back({ textureId,sf::IntRect(256,256 * 5,256,256) });
	//	animation.AddClip(clip);
	//}
	//{
	//	AnimationClip clip;
	//	clip.id = "Idle_Down";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;

	//	clip.frames.push_back({ textureId,sf::IntRect(256,256 * 3,256,256) });
	//	clip.frames.push_back({ textureId,sf::IntRect(256 * 2,256 * 5,256,256) });
	//	animation.AddClip(clip);
	//}
	//{
	//	AnimationClip clip;
	//	clip.id = "Idle_Up";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;

	//	clip.frames.push_back({ textureId,sf::IntRect(256 * 2,256 * 3,256,256) });
	//	clip.frames.push_back({ textureId,sf::IntRect(256 * 3,256 * 5,256,256) });
	//	animation.AddClip(clip);
	//}

	////Move
	//{
	//	AnimationClip clip;
	//	clip.id = "Move_Side";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;

	//	sf::IntRect coord(0, 0, 256, 256);
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		clip.frames.push_back({ textureId,coord });
	//		coord.left += coord.width;
	//	}
	//	animation.AddClip(clip);
	//}
	//{
	//	AnimationClip clip;
	//	clip.id = "Move_Up";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;

	//	sf::IntRect coord(0, 256, 256, 256);
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		clip.frames.push_back({ textureId,coord });
	//		coord.left += coord.width;
	//	}
	//	animation.AddClip(clip);
	//}
	//{
	//	AnimationClip clip;
	//	clip.id = "Move_Down";
	//	clip.fps = 10;
	//	clip.loopType = AnimationLoopTypes::Loop;

	//	sf::IntRect coord(0, 256 * 2, 256, 256);
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		clip.frames.push_back({ textureId,coord });
	//		coord.left += coord.width;
	//	}
	//	animation.AddClip(clip);
	//}

	//파싱으로 로드하는 것 추가, at resourceMgr
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/IdleBack.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/IdleFront.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/IdleLeft.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/MoveLeft.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/MoveBack.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/MoveFront.csv");

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/IdleBack.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/IdleFront.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/IdleLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/MoveLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/MoveBack.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/MoveFront.csv"));
	animation.SetTarget(&sprite);

	SetOrigin(Origins::MC);


	clipInfos.push_back({ "IdleLeft", "MoveLeft", false, Utils::Normalize({ -1.f, -1.f }) });
	clipInfos.push_back({ "IdleBack", "MoveBack", true, {0.f, -1.f} });
	clipInfos.push_back({ "IdleLeft", "MoveLeft", true, Utils::Normalize({ 1.f, -1.f }) });

	clipInfos.push_back({ "IdleLeft", "MoveLeft", false, {-1.f, 0.f} });
	clipInfos.push_back({ "IdleLeft", "MoveLeft", true, {1.f, 0.f} });

	clipInfos.push_back({ "IdleLeft", "MoveLeft", false, Utils::Normalize({ -1.f, 1.f }) });
	clipInfos.push_back({ "IdleFront", "MoveFront", true,{0.f, 1.f} });
	clipInfos.push_back({ "IdleLeft", "MoveLeft", true, Utils::Normalize({ 1.f, 1.f }) });

}

void Player2::Reset()
{
	animation.Play("IdleFront");
	SetOrigin(origin);
	SetPosition({ 0, 0 });
	SetFlipX(false);

	currentClipInfo = clipInfos[6];
}

void Player2::Update(float dt)
{
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

	if (direction.x != 0.f || direction.y != 0.f)
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

	if (animation.GetCurrentClipId() != clipId)
	{
		animation.Play(clipId);
	}

	animation.Update(dt);
}

bool Player2::GetFlipX() const
{
	return filpX;
}

void Player2::SetFlipX(bool filp)
{
	filpX = filp;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !filpX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}