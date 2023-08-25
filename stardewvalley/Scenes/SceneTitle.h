#pragma once
#include "Scene.h"

class SpriteGo;
class UiButton;
class Bird;

class SceneTitle : public Scene
{
protected:
	SpriteGo* titleBg;
	SpriteGo* logo;
	SpriteGo* mountFront;
	SpriteGo* mountBack;
	SpriteGo* bush;
	SpriteGo* star;

	UiButton* start;  
	UiButton* exit;
	UiButton* load;
	UiButton* editor;

	Bird* bird1;
	Bird* bird2;

	float time;
	float timer;
	float viewPos = 0.f;


public:
	bool loadData = false;
	SceneTitle();
	virtual ~SceneTitle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void ShowStartButton();
	void ShowExitButton();
	void ShowLoadButton();
	void ShowEditorButton();
};

