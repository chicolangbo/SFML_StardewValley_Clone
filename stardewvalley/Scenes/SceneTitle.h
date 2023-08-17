#pragma once
#include "Scene.h"

class SpriteGo;
class UiButton;

class SceneTitle : public Scene
{
protected:
	SpriteGo* titleBg;
	SpriteGo* logo;

	UiButton* start;  
	UiButton* exit;  
public:
	SceneTitle();
	virtual ~SceneTitle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

