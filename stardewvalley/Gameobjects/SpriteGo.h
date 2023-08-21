#pragma once
#include "GameObject.h"
class SpriteGo : public GameObject
{
protected:

public:
	sf::Sprite sprite;
	std::string textureId;
	// 김민지, 230807, 추가
	std::string nickName = nullptr;
	//
	// 김민지, 230809, 콜라이더 추가
	sf::RectangleShape collider;
	bool colliderOnOff = true;
	//

	// 김민지, 230807, 스프라이트시트 속 단일이미지 사용 가능하게끔 추가
	// 윤유림, 230808, 닉네임 수정
	SpriteGo(const std::string& textureId = "", const std::string& n = "", const std::string& nickName = "");

	//SpriteGo(const std::string& textureId = "", const std::string& n = "", const std::string& nickName = "");
	//

	virtual ~SpriteGo() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	// 김민지, 230808, 콜라이더 연동 가능하게끔 추가
	virtual void SetScale(float x, float y);
	virtual void SetScale(const sf::Vector2f& p);
	//

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	//임형준, 230811, 콜라이더 리턴해주는 함수 추가
	sf::FloatRect GetCollider();

	void Setting(std::string textureId, std::string n, std::string nickName);

	//윤유림, 230821, 콜라이더 수동으로 크기 변경해주는 함수
	void SetColliderSize(sf::Vector2f size);
};

