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

	if (!load)
	{
		date = 0;
		day = 0;
		level = 0;
		currentday = 0;
		index = { 0, 0 };
		//isWatered = false;
	}
	else
	{
		sprite.setTextureRect(RESOURCE_MGR.GetTextureRect(nickName[level - 1]));
		if (level == 4)
		{
			canHarvest = true;
		}
	}
	bang = false;
	animationTime = 0.7;
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Crop.csv"));
	animation.SetTarget(&sprite);

	SetOrigin(Origins::ML);
}

void Crop::Update(float dt)
{
	SpriteGo::Update(dt);
	animation.Update(dt);

	cout << isWatered << endl;

	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

	int tempcurrentday = sceneGame->GetDay();
	if (tempcurrentday != currentday)
	{
		currentday = tempcurrentday;
		if (isWatered && level<=4)
		{
			day++;
			LevelUp();
		}
		isWatered = false;
	}

	if (bang)
	{
		cout << "bang" << endl;
		SetScale(1.125f, 1.125f);
		sprite.setColor(sf::Color(52, 134, 46, 255));
		animation.Play("Crop");
		bang = false;
	}
	if (animation.GetCurrentClipId() == "Crop")
	{
		time += dt;
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

void Crop::LoadData(CropLoadData ldata)
{
	index.x = ldata.x;
	index.y = ldata.y;
	date = ldata.date;
	day = ldata.day;
	level = ldata.level;
	currentday = ldata.curday;
	isWatered = ldata.water;
	sortLayer = ldata.sortl;
	sortOrder = ldata.sorto;
	//LevelUp();
	load = true;
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

CropSaveData Crop::GetLoadData()
{
	cropSaveData =
	{
		id,
		date,
		day,
		currentday,
		level,
		index,
		isWatered,
		sortLayer,
		sortOrder
	};
	return cropSaveData;
}
