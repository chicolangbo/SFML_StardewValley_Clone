#include "stdafx.h"
#include "SliceImageGo.h"
#include "ResourceMgr.h"

SliceImageGo::SliceImageGo(const std::string& textureId, const string& name, sf::Rect<float> centerRect, sf::Rect<float> size, int vc )
	:VertexArrayGo(textureId, name), centerRect(centerRect), fullSize(size), vertexCount(vc)
{
}

//void SliceImageGo::SetTexture(sf::Texture& texture)
//{
//	this->texture = &texture;
//	vertexArray.setPrimitiveType(sf::Quads);
//	vertexArray.resize(36);
//
//	this->centerRect = centerRect;
//	this->fullSize = size;
//
//	SetTextureSize(centerRect, fullSize);
//	SetSize({ size.width, size.height });
//}

void SliceImageGo::SetTextureSize()
{
	vector<float> textureHorizontal;
	vector<float> textureVertical;

	textureHorizontal.push_back(fullSize.left);
	textureHorizontal.push_back(centerRect.left);
	textureHorizontal.push_back(centerRect.left + centerRect.width);
	textureHorizontal.push_back(fullSize.left + fullSize.width);

	if (vertexCount == NINE_SLICE)
	{
		textureVertical.push_back(fullSize.top);
		textureVertical.push_back(centerRect.top);
		textureVertical.push_back(centerRect.top + centerRect.height);
		textureVertical.push_back(fullSize.top + fullSize.height);

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				int index = (i * 3 + j) * 4;
				vertexArray[index].texCoords = { textureHorizontal[j], textureVertical[i] };
				vertexArray[index + 1].texCoords = { textureHorizontal[j + 1], textureVertical[i] };
				vertexArray[index + 2].texCoords = { textureHorizontal[j + 1], textureVertical[i + 1] };
				vertexArray[index + 3].texCoords = { textureHorizontal[j], textureVertical[i + 1] };
			}
		}
	}
	else if (vertexCount == THREE_SLICE)
	{
		textureVertical.push_back(fullSize.top);
		textureVertical.push_back(fullSize.top + fullSize.height);

		for (int i = 0; i < 3; ++i)
		{
			int index = i * 4;
			vertexArray[index].texCoords = { textureHorizontal[i], textureVertical[0] };
			vertexArray[index + 1].texCoords = { textureHorizontal[i+1], textureVertical[0] };
			vertexArray[index + 2].texCoords = { textureHorizontal[i+1], textureVertical[1] };
			vertexArray[index + 3].texCoords = { textureHorizontal[i], textureVertical[1] };
		}
	}
}

void SliceImageGo::SetSize(sf::Vector2f size)
{
	vector<float> positionX;
	vector<float> positionY;
	sf::Vector2f borderSize = { fullSize.width - centerRect.width, fullSize.height - centerRect.height };

	if (vertexCount == NINE_SLICE)
	{
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
			positionY.push_back(fullSize.top + borderSize.y);
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
}

void SliceImageGo::SetSize(float w)
{
	vector<float> positionX;
	vector<float> positionY;
	sf::Vector2f borderSize = { fullSize.width - centerRect.width, fullSize.height };

	if (borderSize.x < w)
	{
		positionX.push_back(fullSize.left);
		positionX.push_back(centerRect.left);
		positionX.push_back(centerRect.left + (w - borderSize.x));
		positionX.push_back(fullSize.left + w);
	}
	else
	{
		positionX.push_back(fullSize.left);
		positionX.push_back(centerRect.left);
		positionX.push_back(centerRect.left);
		positionX.push_back(fullSize.left + borderSize.x);
	}

	if (vertexCount == THREE_SLICE)
	{
		positionY.push_back(fullSize.top);
		positionY.push_back(fullSize.top + fullSize.height);

		for (int i = 0; i < 3; ++i)
		{
			int index = i * 4;
			vertexArray[index].position = { positionX[i], positionY[0] };
			vertexArray[index + 1].position = { positionX[i + 1], positionY[0] };
			vertexArray[index + 2].position = { positionX[i + 1], positionY[1] };
			vertexArray[index + 3].position = { positionX[i], positionY[1] };
		}
	}
}

void SliceImageGo::Init()
{
	VertexArrayGo::Init();
	this->texture = RESOURCE_MGR.GetTexture(textureId);
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(vertexCount);
	SetTextureSize();
	SetSize({ fullSize.width, fullSize.height });
}

void SliceImageGo::Release()
{
	VertexArrayGo::Release();
}

void SliceImageGo::Reset()
{
	//SetTexture(*RESOURCE_MGR.GetTexture(textureId), centerRect, fullSize);
}

void SliceImageGo::Update(float dt)
{
	VertexArrayGo::Update(dt);
}

sf::Vector2f SliceImageGo::GetSize()
{
	if (vertexCount == NINE_SLICE)
	{
		float x = vertexArray[9].position.x - vertexArray[0].position.x;
		float y = vertexArray[34].position.y - vertexArray[0].position.y;
		return sf::Vector2f{ x,y };
	}
	else
	{
		float x = vertexArray[9].position.x - vertexArray[0].position.x;
		float y = vertexArray[3].position.y - vertexArray[0].position.y;
		return sf::Vector2f{ x,y };
	}
}
