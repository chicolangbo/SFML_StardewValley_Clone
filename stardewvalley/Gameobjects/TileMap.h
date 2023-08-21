#pragma once
#include "VertexArrayGo.h"

struct Tile
{
	int x = 0;
	int y = 0;
	float texLeft;
	float texTop;
	float texWidth;
	float texHeight;
	//int texIndex = 0;
	//TileType type;
};

//
class TileMap : public VertexArrayGo
{
protected:
	//sf::Vector2f tileSize = { 80.f, 45.f };//{ 32.f, 32.f }; //80.f, 80.f, 2.5น่(1280/512)
	sf::Vector2f tileSize = { 72.f, 72.f }; //48
	sf::Vector2f texSize = { 16.f, 16.f };
	sf::Vector2i size = { 20, 20 };

	int count = 0;
	
public:
	std::vector<Tile> tiles;

	bool isLood = false;

	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool Load(const std::string& filePath);
	bool Load(int col, int row, float texX, float texY);

	bool Save(const std::string& filePath);

	sf::Vector2i GetSize();
	sf::Vector2f GetTileSize();
	sf::Vector2f GetTileMapSize();
	int GetTileIndex(int x, int y);
	Tile& GetTile(const int x, const int y);
	void setTilesize(float x, float y);
	void setTexSize(float x, float y);
	//void setScale(float scaleX, float scaleY);

	void ChangeTexRect(int x, int y, sf::IntRect texRect);
	
};
