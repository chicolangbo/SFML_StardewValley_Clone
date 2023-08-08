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

	// 김민지, 230807, 스프라이트시트 속 단일이미지 사용 가능하게끔 추가
	//SpriteGo(const std::string& textureId, const std::string& n);

	SpriteGo(const std::string& textureId = "", const std::string& n = "", const std::string& nickName = "");
	//

	virtual ~SpriteGo() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;


};

