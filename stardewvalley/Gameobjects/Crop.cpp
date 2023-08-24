#include "stdafx.h"
#include "Crop.h"
#include "DataTableMgr.h"
#include "CropTable.h"
#include "HoeDirt.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "ResourceMgr.h"

Crop::Crop(const string& textureId, const string& n, const string& nickname)
	:SpriteGo(textureId, n, nickname)
{
}

Crop::~Crop()
{
}

void Crop::Init()
{
	SpriteGo::Init();

	SpriteGo::textureId = "graphics/crops.png";

	SetScale({ 4.5f, 4.5f });

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Crop.csv"));
	animation.SetTarget(&sprite);
}

void Crop::Release()
{
	SpriteGo::Release();

}

void Crop::Reset()
{
	SpriteGo::Reset();

	date = 0; //심은 날짜 
	day = 0; //심은 이후의 날짜
	level = 0;
	currentday = 0;
	index = { 0, 0 };
	isWatered = false;
	bang = false;

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Crop.csv"));
	animation.SetTarget(&sprite);

	SetOrigin(Origins::ML);
}

void Crop::Update(float dt)
{
	SpriteGo::Update(dt);

	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

	int tempcurrentday = sceneGame->GetDay();
	if (tempcurrentday != currentday)
	{
		currentday = tempcurrentday;
		if (isWatered && level<4)
		{
			day++;
			LevelUp();
		}
		isWatered = false;
	}

	if (bang)
	{
		//SetScale(1.5f, 1.5f);
		//SetPosition(position);
		//SetOrigin(Origins::BC);
		animation.Play("Crop");
		bang = false;
	}
}

void Crop::SetIndex(int x, int y)
{
	index = sf::Vector2i(x, y);
}

void Crop::SetType(CropId id)
{
	this->id = id;
	const cropInfo& info = DATATABLE_MGR.Get<CropTable>(DataTable::Ids::Crop)->Get(id);

	for (int i = 0; i < 4; i++)
	{
		period[i] = info.period[i];
		nickName[i] = info.nickName[i];
		allPeriod += period[i];
	}
	for (int i = 0; i < 2; i++)
	{
		seedNick[i] = info.seedNick[i];
	}

	int randNum = Utils::RandomRange(0, 2);
	SpriteGo::nickName = seedNick[randNum];
}

void Crop::SetDirtTile(HoeDirt* tile)
{
	dirtTile = tile;
	index = dirtTile->GetIndex();
}

void Crop::SetDate(int date)
{
	this->date = date;
	currentday = date;
}

void Crop::LevelUp()
{
	if (period[level] == day)
	{
		level++;
		sprite.setTextureRect(RESOURCE_MGR.GetTextureRect(nickName[level - 1]));
		day = 0;

		cout << (int)id << "," << level << endl;
	}
	if (level == 4)
		canHarvest = true;
}

void Crop::FullLevUp()
{
	level = 4;
	sprite.setTextureRect(RESOURCE_MGR.GetTextureRect(nickName[level - 1]));
	canHarvest = true;
}
