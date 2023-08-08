#pragma once
#include "Scene.h"
class UiButton;

class SceneEditor : public Scene
{
protected:

	sf::Vector2f centerPos;
	UiButton* buttonCreate;

public:
	SceneEditor();
	virtual ~SceneEditor() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

