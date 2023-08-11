#pragma once
#include "VertexArrayGo.h"

class SliceImageGo : public VertexArrayGo
{
protected:
	sf::Rect<float> centerRect;
	sf::Rect<float> fullSize;
	int vertexCount = 0;

public:
	SliceImageGo(const std::string& textureId, const string& name, sf::Rect<float> centerRect, sf::Rect<float> size, int vc );

	// 기존 texture 9등분
	//virtual void SetTexture(sf::Texture& texture, sf::Rect<float> centerRect, sf::Rect<float> size);
	void SetTextureSize();

	// 리사이즈
	virtual void SetSize(sf::Vector2f size);
	virtual void SetSize(float w);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
};

#define NINE_SLICE	36
#define THREE_SLICE 12