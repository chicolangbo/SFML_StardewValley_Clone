#include "stdafx.h"
#include "NineSlice.h"
#include "ResourceMgr.h"

NineSlice::NineSlice(const std::string& textureId, const string& name, sf::Rect<float> centerRect, sf::Rect<float> size )
	:VertexArrayGo(textureId, name), centerRect(centerRect), fullSize(size)
{
}

void NineSlice::SetTexture(sf::Texture& texture, sf::Rect<float> centerRect, sf::Rect<float> size)
{
	this->texture = &texture;
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(36);

	this->centerRect = centerRect;
	this->fullSize = size;

	SetTextureSize(centerRect, fullSize);
	SetSize({ size.width, size.height });
}

void NineSlice::SetTextureSize(sf::Rect<float> centerRect, sf::Rect<float> fullSize)
{
	vector<float> textureHorizontal;
	vector<float> textureVertical;

	textureHorizontal.push_back(fullSize.left);
	textureHorizontal.push_back(centerRect.left);
	textureHorizontal.push_back(centerRect.left + centerRect.width);
	textureHorizontal.push_back(fullSize.left + fullSize.width);

	textureVertical.push_back(fullSize.top);
	textureVertical.push_back(centerRect.top);
	textureVertical.push_back(centerRect.top + centerRect.height);
	textureVertical.push_back(fullSize.top + fullSize.height);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int index = (i * 3 + j) * 4;
			vertexArray[index].texCoords = { textureHorizontal[j], textureVertical[i] };
			vertexArray[index + 1].texCoords = { textureHorizontal[j + 1], textureVertical[i] };
			vertexArray[index + 2].texCoords = { textureHorizontal[j + 1], textureVertical[i + 1] };
			vertexArray[index + 3].texCoords = { textureHorizontal[j], textureVertical[i + 1] };
		}
	}
}

void NineSlice::SetSize(sf::Vector2f size)
{
	vector<float> positionX;
	vector<float> positionY;
	sf::Vector2f borderSize = { fullSize.width - centerRect.width, fullSize.height - centerRect.height };

	if (borderSize.x < size.x)
	{
		positionX.push_back(fullSize.left);
		positionX.push_back(centerRect.left);
		positionX.push_back(centerRect.left + (size.x - borderSize.x));
		positionX.push_back(fullSize.left + size.x);
	}
	else
	{
		positionX.push_back(fullSize.left);
		positionX.push_back(borderSize.x * 0.5f);
		positionX.push_back(borderSize.x * 0.5f);
		positionX.push_back(size.x);
	}

	if (borderSize.y < size.y)
	{
		positionY.push_back(fullSize.top);
		positionY.push_back(centerRect.top);
		positionY.push_back(centerRect.top + (size.y - borderSize.y));
		positionY.push_back(fullSize.top + size.y);
	}
	else
	{
		positionY.push_back(fullSize.top);
		positionY.push_back(borderSize.y * 0.5f);
		positionY.push_back(borderSize.y * 0.5f);
		positionY.push_back(size.y);
	}


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int index = (i * 3 + j) * 4;
			vertexArray[index].position = { positionX[j], positionY[i] };
			vertexArray[index + 1].position = { positionX[j + 1], positionY[i] };
			vertexArray[index + 2].position = { positionX[j + 1], positionY[i + 1] };
			vertexArray[index + 3].position = { positionX[j], positionY[i + 1] };
		}
	}
}

void NineSlice::Init()
{
	VertexArrayGo::Init();
	SetTexture(*RESOURCE_MGR.GetTexture(textureId), centerRect, fullSize);
}

void NineSlice::Release()
{
	VertexArrayGo::Release();
}

void NineSlice::Reset()
{
	//SetTexture(*RESOURCE_MGR.GetTexture(textureId), centerRect, fullSize);
}

void NineSlice::Update(float dt)
{
	VertexArrayGo::Update(dt);
}