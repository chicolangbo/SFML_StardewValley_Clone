#pragma once
#include "SpriteGo.h"
class UiButton : public SpriteGo
{
protected:
	bool isHover = false;

public:
	sf::Text text;
	// �����, 230811, SpriteGo�� ���缭 ����
	//UiButton(const std::string& textureId, const std::string& n);
	UiButton(const std::string& textureId, const std::string& n, const std::string& nickName = "");
	//
	virtual ~UiButton() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	// �����, 230813, �߰�
	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);
	//
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void Click();

	function<void()> OnClick;
	function<void()> OnEnter; //Ŀ���� ������ ���� ��
	function<void()> OnExit; //�������� ������

};

