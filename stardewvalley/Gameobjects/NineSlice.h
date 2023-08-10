#pragma once
#include "VertexArrayGo.h"
class NineSlice : public VertexArrayGo
{
protected:
	sf::Rect<float> centerRect;
	sf::Rect<float> spriteSize;
public:
	NineSlice(const std::string& textureID, sf::Rect<float> centerRect, sf::Rect<float> size, const string& name = "");

	virtual void SetTexture(sf::Texture& texture, sf::Rect<float> centerRect, sf::Rect<float> size);
	void SetTextureSize(sf::Rect<float> centerRect, sf::Rect<float> spriteSize);
	virtual void SetSize(sf::Vector2f size);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
};