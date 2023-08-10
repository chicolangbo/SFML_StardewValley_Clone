#pragma once
#include "VertexArrayGo.h"
class NineSlice : public VertexArrayGo
{
protected:
	sf::Rect<float> centerRect;
	sf::Rect<float> fullSize;
public:
	NineSlice(const std::string& textureId, const string& name, sf::Rect<float> centerRect, sf::Rect<float> size );

	virtual void SetTexture(sf::Texture& texture, sf::Rect<float> centerRect, sf::Rect<float> size);
	void SetTextureSize(sf::Rect<float> centerRect, sf::Rect<float> fullSize);
	virtual void SetSize(sf::Vector2f size);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
};