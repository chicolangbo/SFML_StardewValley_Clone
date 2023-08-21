#include "stdafx.h"
#include "TileMap.h"
#include "rapidcsv.h"

TileMap::TileMap(const std::string& textureId, const std::string& n)
    : VertexArrayGo(textureId, n)
{
}

TileMap::~TileMap()
{
}

bool TileMap::Load(const std::string& filePath)
{
    rapidcsv::Document doc(filePath);
    count = doc.GetRowCount();
    size.x = doc.GetCell<int>("cols", 0);
    size.y = doc.GetCell<int>("rows", 0);

    for (int i = 2; i < count; i++)
    {
        Tile tile;

        auto rows = doc.GetRow<float>(i);
        tile.x = (rows[0]);
        tile.y = (rows[1]);
        tile.texLeft = (rows[2]);
        tile.texTop = (rows[3]);
        tile.texWidth = (rows[4]);
        tile.texHeight = (rows[5]);

        tiles.push_back(tile);
    }

    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(size.x * size.y * 4);
    sf::Vector2f startPos = { 0, 0 };
    sf::Vector2f currPos = startPos;

    sf::Vector2f offsets[4] =
    {
        { 0.f, 0.f },
        { tileSize.x, 0.f },
        { tileSize.x, tileSize.y },
        { 0.f, tileSize.y }
    };

    for (int i = 0; i < size.y; ++i)
    {
        for (int j = 0; j < size.x; ++j)
        {
            int tileIndex = size.x * i + j;

            Tile& tile = tiles[tileIndex];

            // 텍스처 좌표 계산
            sf::Vector2f texOffsets[4] =
            {
                { tile.texLeft, tile.texTop },
                { tile.texLeft + tile.texWidth, tile.texTop },
                { tile.texLeft + tile.texWidth, tile.texTop + tile.texHeight },
                { tile.texLeft, tile.texTop + tile.texHeight }
            };

            for (int k = 0; k < 4; ++k)
            {
                int vertexIndex = tileIndex * 4 + k;
                vertexArray[vertexIndex].position = currPos + offsets[k];
                vertexArray[vertexIndex].texCoords = texOffsets[k];
            }
            currPos.x += tileSize.x;
        }
        currPos.x = startPos.x;
        currPos.y += tileSize.y;
    }
    isLood = true;
    return true;

    /*rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
    size = { (int)map.GetColumnCount(), (int)map.GetRowCount() };

    for (int i = 0; i < size.y; ++i)
    {
        for (int j = 0; j < size.x; ++j)
        {
            Tile tile;
            tile.x = j;
            tile.y = i;
            tile.texIndex = map.GetCell<int>(j, i); //타일 종류
            tiles.push_back(tile);
        }
    }
    sf::Vector2f texOffsets[4] =
    {
        { 0.f, 0.f },
        { texSize.x, 0.f },
        { texSize.x, texSize.y },
        { 0.f, texSize.y }
    };


    // resize the vertex array to fit the level size
    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(size.x * size.y * 4);
    sf::Vector2f startPos = { 0, 0 };
    sf::Vector2f currPos = startPos;

    sf::Vector2f offsets[4] =
    {
        { 0.f, 0.f },
        { tileSize.x, 0.f },
        { tileSize.x, tileSize.y },
        { 0.f, tileSize.y }
    };

    for (int i = 0; i < size.y; ++i)
    {
        for (int j = 0; j < size.x; ++j)
        {
            int tileIndex = size.x * i + j;
            int texIndex = tiles[tileIndex].texIndex;
            for (int k = 0; k < 4; ++k)
            {
                int vertexIndex = tileIndex * 4 + k;
                vertexArray[vertexIndex].position = currPos + offsets[k];
                vertexArray[vertexIndex].texCoords = texOffsets[k];
                vertexArray[vertexIndex].texCoords.x += texSize.x * texIndex;
            }
            currPos.x += tileSize.x;
        }
        currPos.x = startPos.x;
        currPos.y += tileSize.y;
    }

    isLood = true;
    return true;*/
}

//230809, 윤유림, 행+렬 수로 로드
bool TileMap::Load(int col, int row, float texX, float texY)
{
    size = sf::Vector2i(col, row);

    for (int i = 0; i < size.y; ++i)
    {
        for (int j = 0; j < size.x; ++j)
        {
            Tile tile;
            tile.x = j;
            tile.y = i;
            tile.texLeft = texX;
            tile.texTop = texY;
            tile.texWidth = texSize.x;
            tile.texHeight = texSize.y;
            tiles.push_back(tile);
        }
    }
    // resize the vertex array to fit the level size
    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(size.x * size.y * 4);
    sf::Vector2f startPos = { 0, 0 };
    sf::Vector2f currPos = startPos;

    sf::Vector2f texOffsets[4] =
    {
        { texX, texY },
        { texSize.x + texX, texY },
        { texSize.x + texX, texSize.y + texY},
        { texX, texSize.y + texY }
    };
    sf::Vector2f offsets[4] =
    {
        { 0.f, 0.f },
        { tileSize.x, 0.f },
        { tileSize.x, tileSize.y },
        { 0.f, tileSize.y }
    };

    for (int i = 0; i < size.y; ++i)
    {
        for (int j = 0; j < size.x; ++j)
        {
            int tileIndex = size.x * i + j;
            for (int k = 0; k < 4; ++k)
            {
                int vertexIndex = tileIndex * 4 + k;
                vertexArray[vertexIndex].position = currPos + offsets[k];
                vertexArray[vertexIndex].texCoords = texOffsets[k];
            }
            currPos.x += tileSize.x;
        }
        currPos.x = startPos.x;
        currPos.y += tileSize.y;
    }
    isLood = true;
    return true;
}

bool TileMap::Save(const std::string& filePath)
{
    std::ofstream outputFile(filePath);

    if (!outputFile.is_open())
    {
        cout << "ERR: 파일을 열 수 없습니다." << endl;
        return false;
    }

    // 파일 헤더
    outputFile << "cols,rows" << endl;
    outputFile << size.x << "," << size.y << endl;

    outputFile << "indexX,indexY,left,top,width,height" << endl;

    for (int i = 0; i < tiles.size(); ++i)
    {
        Tile& tile = tiles[i];
        // 각 타일의 정보를 파일에 쓰기
        outputFile << tile.x << "," << tile.y << "," << tile.texLeft << ","
            << tile.texTop << "," << tile.texWidth << "," << tile.texHeight << endl;
    }

    outputFile.close();
    return true;
}

sf::Vector2f TileMap::GetTileMapSize()
{
    return sf::Vector2f{tileSize.x* size.x, tileSize.y* size.y};
}

int TileMap::GetTileIndex(int x, int y)
{
    for (int i = 0; i < tiles.size(); i++)
    {
        Tile tile = tiles.at(i);
        if (tile.x == x && tile.y == y)
        {
            return tile.texIndex;
        }
    }
    /*return -1;*/
    return 0;
}

Tile& TileMap::GetTile(const int x, const int y)
{
    for (int i = 0; i < tiles.size(); i++)
    {
        Tile tile = tiles.at(i);
        if (tile.x == x && tile.y == y)
        {
            return tile;
        }
    }
    cout << "ERR: No Tile" << endl;
    exit(1);
}

void TileMap::setTilesize(float x, float y)
{
    tileSize = { x, y };
}

void TileMap::setTexSize(float x, float y)
{
    texSize = { x, y };
}

//void TileMap::setScale(float scaleX, float scaleY)
//{
//    // 뷰의 크기를 설정
//    tileSize.x *= scaleX;
//    tileSize.y *= scaleY;
//
//    // 타일맵 내의 타일들의 위치와 크기를 조정
//    sf::Vector2f tileOffsets[4] =
//    {
//        { 0.f, 0.f },
//        { tileSize.x, 0.f },
//        { tileSize.x, tileSize.y },
//        { 0.f, tileSize.y }
//    };
//
//    sf::Vector2f texOffsets[4] =
//    {
//        { 0.f, 0.f },
//        { texSize.x, 0.f },
//        { texSize.x, texSize.y },
//        { 0.f, texSize.y }
//    };
//
//    sf::Vector2f startPos = { 0.f, 0.f };
//    sf::Vector2f currPos = startPos;
//
//    for (int i = 0; i < size.y; ++i)
//    {
//        for (int j = 0; j < size.x; ++j)
//        {
//            int tileIndex = size.x * i + j;
//            int texIndex = tiles[tileIndex].texIndex;
//            for (int k = 0; k < 4; ++k)
//            {
//                int vertexIndex = tileIndex * 4 + k;
//                vertexArray[vertexIndex].position = currPos + tileOffsets[k];
//                vertexArray[vertexIndex].texCoords = texOffsets[k];
//                vertexArray[vertexIndex].texCoords.x += texSize.x * texIndex;
//            }
//            currPos.x += tileSize.x;
//        }
//        currPos.x = startPos.x;
//        currPos.y += tileSize.y;
//    }
//}

void TileMap::ChangeTexRect(int x, int y, sf::IntRect texRect)
{
    //x, y, left, top, height, width 파일에 저장
    sf::Vector2f texOffsets[4] =
    {
        {(float)texRect.left, (float)texRect.top},
        {(float)texRect.left + (float)texRect.width, (float)texRect.top},
        {(float)texRect.left + (float)texRect.width, (float)texRect.top + (float)texRect.height},
        {(float)texRect.left, (float)texRect.top + (float)texRect.height}
    };

    if (x >= 0 && x < size.x && y >= 0 && y < size.y)
    {
        int tileIndex = size.x * y + x;
        tiles[tileIndex].texTop = texRect.top;
        tiles[tileIndex].texLeft = texRect.left;
        for (int k = 0; k < 4; ++k)
        {
            int vertexIndex = tileIndex * 4 + k;
            vertexArray[vertexIndex].texCoords = texOffsets[k];
        }
    }
    else
    {
        cout << "ERR: 잘못된 타일 위치" << endl;
    }
}

sf::Vector2i TileMap::GetSize()
{
    return size;
}

sf::Vector2f TileMap::GetTileSize()
{
    return tileSize;
}

