#pragma once

#define _USE_MATH_DEFINES

enum class Languages
{
	KOR,
	ENG,
	JP,
	COUNT,
};

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
	AnimationClip,
};

enum class SceneId
{
	None = -1,
	Game,
	Editor,
	Count,
};

enum class MotionId
{
	Idle,
	Move
};

//230809, 윤유림, 오브젝트 추가, tile type 추가
enum class TileType
{
	Dirt,
	Water,
	Grass,
	Cliff
};

enum class ObjType
{
	Stone,
	Weed,
	Tree,
	Timber
};

//
#include "AnimationClip.h"