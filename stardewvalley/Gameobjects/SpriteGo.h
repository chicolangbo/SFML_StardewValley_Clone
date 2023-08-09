#pragma once
#include "GameObject.h"
class SpriteGo : public GameObject
{
protected:

public:
	sf::Sprite sprite;
	std::string textureId;
	// �����, 230807, �߰�
	std::string nickName = nullptr;
	//
	// �����, 230809, �ݶ��̴� �߰�
	sf::RectangleShape collider;
	bool colliderOnOff = true;
	//

	// �����, 230807, ��������Ʈ��Ʈ �� �����̹��� ��� �����ϰԲ� �߰�
	// ������, 230808, �г��� ����
	SpriteGo(const std::string& textureId = "", const std::string& n = "");

	//SpriteGo(const std::string& textureId = "", const std::string& n = "", const std::string& nickName = "");
	//

	virtual ~SpriteGo() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	// �����, 230808, �ݶ��̴� ���� �����ϰԲ� �߰�
	virtual void SetScale(float x, float y);
	virtual void SetScale(const sf::Vector2f& p);
	//

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;


};

