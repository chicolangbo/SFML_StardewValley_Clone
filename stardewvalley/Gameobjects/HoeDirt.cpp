#include "stdafx.h"
#include "HoeDirt.h"
#include "Utils.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "Crop.h"

HoeDirt::HoeDirt(const string& n, const string& textureId, const string& dirtNick, const string& waterNick)
	:GameObject(n), textureId(textureId), dirtNick(dirtNick), waterNick(waterNick)
{
}

HoeDirt::~HoeDirt()
{
}

void HoeDirt::Init()
{
	load = false;
}

void HoeDirt::Release()
{
}

void HoeDirt::Reset()
{
	sf::Texture* tex = RESOURCE_MGR.GetTexture(textureId);
	if (tex != nullptr)
	{
		dirt.setTexture(*tex);
		waterDirt.setTexture(*tex);
	}
	sf::IntRect texRect = RESOURCE_MGR.GetTextureRect(dirtNick);
	dirt.setTextureRect(texRect);

	texRect = RESOURCE_MGR.GetTextureRect(waterNick);
	waterDirt.setTextureRect(texRect);

	dirt.setScale({ 4.5f, 4.5f });
	waterDirt.setScale({ 4.5f, 4.5f });

	SetOrigin(origin);

	if (!load)
	{
		day = 0;
		currentDay = 0;
		plantedCrop = false;
		isWatered = false;
	}
}

void HoeDirt::Update(float dt)
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

	int tempcurrentday = sceneGame->GetDay();
	if (tempcurrentday != currentDay)
	{
		currentDay = tempcurrentday;
		day++;
		isWatered = false;
	}
}

void HoeDirt::Draw(sf::RenderWindow& window)
{
	window.draw(dirt);
	if (isWatered)
	{
		window.draw(waterDirt);
	}
}

void HoeDirt::SetPosition(const sf::Vector2f& p)
{
	position = p;
	dirt.setPosition(p);
	waterDirt.setPosition(p);
}

void HoeDirt::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	dirt.setPosition(position);
	waterDirt.setPosition(position);
}

void HoeDirt::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(dirt, origin);
		Utils::SetOrigin(waterDirt, origin);
	}
}

void HoeDirt::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	dirt.setOrigin(x, y);
	waterDirt.setOrigin(x, y);
}

void HoeDirt::SetIsWatered(bool is)
{
	isWatered = is;
	if (crop != nullptr)
	{
		crop->SetIsWatered(is);
	}
}

void HoeDirt::PlantCrop(Crop* c)
{
	crop = c;
	cropId = crop->GetCropId();
	plantedCrop = true;
}

void HoeDirt::RemoveCrop()
{
	crop = nullptr;
	plantedCrop = false;
	cropId = CropId::None;
}
