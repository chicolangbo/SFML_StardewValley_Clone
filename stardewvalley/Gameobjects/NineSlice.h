#pragma once
#include "GameObject.h"

class NineSlice :
    public GameObject
{
protected:
	sf::Sprite cornerSprite[4];
	sf::Sprite edgeSprite[4];
	sf::Sprite centerSprite;
	
	sf::FloatRect centerRect;
	int c_width;
	int c_height;
	int width;
	int height;

	std::string textureId;

public:
	NineSlice(const std::string& textureId, const std::string& n, float w, float h);
	virtual ~NineSlice() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void SetScale(float x, float y);
	virtual void SetScale(const sf::Vector2f& p);

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SliceImages();
	void SetSlicePosition();
};

