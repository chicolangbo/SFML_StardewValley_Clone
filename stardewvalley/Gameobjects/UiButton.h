#pragma once
#include "SpriteGo.h"
class UiButton : public SpriteGo
{
protected:
	bool isHover = false;

public:
	sf::Text text;
	// 김민지, 230811, SpriteGo에 맞춰서 수정
	//UiButton(const std::string& textureId, const std::string& n);
	UiButton(const std::string& textureId, const std::string& n, const std::string& nickName = "");
	//
	virtual ~UiButton() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	// 김민지, 230813, 추가
	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);
	//
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void Click();

	function<void()> OnClick;
	function<void()> OnEnter; //커서가 영역에 들어올 때
	function<void()> OnExit; //영역에서 나갈때

};

