#pragma once
#include "VertexArrayGo.h"

struct MapObj
{
	int x = 0;
	int y = 0;
	int texIndex = 0;
	ObjType type;
};

struct Tile
{
	int x = 0;
	int y = 0;
	float texWidth;
	float texHeight;
	float texLeft;
	float texTop;
	int texIndex = 0;
	TileType type;
};

//
class TileMap : public VertexArrayGo
{
protected:
	//sf::Vector2f tileSize = { 80.f, 45.f };//{ 32.f, 32.f }; //80.f, 80.f, 2.5น่(1280/512)
	sf::Vector2f tileSize = { 48.f, 48.f };
	sf::Vector2f texSize = { 16.f, 16.f };
	sf::Vector2i size;
	
public:
	std::vector<Tile> tiles;
	std::vector<MapObj> objs;

	bool isLood = false;

	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool Load(const std::string& filePath);
	bool Load(int col, int row, float texX, float texY);

	sf::Vector2f GetTileSize();
	sf::Vector2f GetTileMapSize();
	int GetTileIndex(int x, int y);
	Tile& GetTile(const int x, const int y);
	void setTilesize(float x, float y);
	void setTexSize(float x, float y);
	void setScale(float scaleX, float scaleY);

	void ChangeTexRect(int x, int y, sf::IntRect texRect);
	
};
