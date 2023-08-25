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
	Title,
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
	Cliff,
	Road
};

enum class ObjType
{
	Stone,
	Weed,
	Tree,
	Timber,
	None
};

enum class  ItemId
{
	none,
	pick,
	ax,
	homi,
	waterCan,
	hook,
	craftBox,
	craftScareCrow,
	craftContainer,
	stone,
	coal,
	branch,
	fiver,
	mapleSeed,
	acorn,
	pineCone,
	parsnipSeed,
	potatoSeed,
	coliSeed,
	parsnip,
	potato,
	coli
};

enum class CropId
{
	Parsnip,
	Potato,
	Cauliflower,
	None,
};

enum class Location
{
	Farm,
	Shop,
	Home
};

struct CropLoadData
{
	int type;
	int x;
	int y;
	int date;
	int day;
	int level;
	int curday;
	int water;
	int sortl;
	int sorto;
};
//
//struct CropSaveData
//{
//	CropId id;
//	int date;
//	int day;
//	int currentday;
//	int level;
//	sf::Vector2i index;
//	bool isWatered;
//	int sortLayer;
//	int sortOrder;
//};

#include "AnimationClip.h"