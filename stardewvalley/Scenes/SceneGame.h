#pragma once
#include "Scene.h"

class VertexArrayGo;
class Player2;
class SpriteGo;
class Wall;
class SliceImageGo;
class Inventory;
class RootingItem;
class QuickInventory;
class RectangleGo;
class ShopTap;
class ShopInterior;
class HomeInterior;

class SceneGame : public Scene
{
protected:
	VertexArrayGo* background;
	sf::FloatRect wallBounds;

	bool enterShop = false;
	bool enterHome = false;
	
	Player2* player2;

	// ¿”Ω√ ∏ 
	SpriteGo* testFarmMap; // ≥Û¿Â ≈Î∏ 
	SpriteGo* houseExterior; // ¡˝ ø‹∫Œ
	SpriteGo* shopExterior; // º• ø‹∫Œ

	ShopTap* shopTap;
	ShopInterior* shopInterior;
	HomeInterior* homeInterior;
	SpriteGo* bedding;

	// INGAME UI
	SpriteGo* energy;
	SpriteGo* info;
	SpriteGo* timeArrow;
	float arrowSpin = 0.f;
	RectangleGo* energyBar; 
	int energys;
	sf::Text textMoney;
	sf::Text textMin;
	sf::Text textHour;
	sf::Text textDay;
	sf::Font font;
	float time = 0.f;
	int min = 0;
	int hour = 6;
	int day = 1;

	std::vector<sf::FloatRect> walls;
	sf::FloatRect playerBound; 
	sf::FloatRect mapBound;

	Inventory* inven;
	std::list<RootingItem*>rootingItems; 
	QuickInventory* quickinven;

	bool off = false;

public:
	SceneGame();
	virtual ~SceneGame() override = default;

	VertexArrayGo* CreateBackGround(sf::Vector2i size, sf::Vector2f tileSize, sf::Vector2f texSize, string textureId);

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SpawnRootingItem(ItemId id);
};

