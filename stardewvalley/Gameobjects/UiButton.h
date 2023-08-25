#pragma once
#include "SpriteGo.h"
class UiButton : public SpriteGo
{
protected:
	bool isHover = false;
	bool isHoverWorld = false;

public:
	sf::Text text;
	//UiButton(const std::string& textureId, const std::string& n);
	UiButton(const std::string& textureId ="", const std::string& n ="", const std::string& nickName = "");
	//
	virtual ~UiButton() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	function<void()> OnClick;
	function<void()> OnEnter;
	function<void()> OnExit;

	function<void()> OnClickWorld;
	function<void()> OnEnterWorld;
	function<void()> OnExitWorld;
};

