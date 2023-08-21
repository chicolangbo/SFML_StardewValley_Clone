#pragma once

class GameObject;

class Scene
{
protected:
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	SceneId sceneId;

	string resourceListPath;

	//std::vector<std::tuple<ResourceTypes, std::string>> resources;

	std::list<GameObject*> gameObjects; 
	std::list<GameObject*> removeGameObjects;

	sf::View worldView;
	sf::View uiView;

	// �����, 230812, ��ũ�� ������ �߰�
	sf::Vector2f windowSize;
	
	sf::RenderWindow& window;

public:
	Scene(SceneId id = SceneId::None);
	virtual ~Scene();

	GameObject* FindGo(const std::string& name);
	void FindGos(std::list<GameObject*>& list, const std::string& name);
	bool Exist(GameObject* go);
	GameObject* AddGo(GameObject* go);
	void RemoveGo(GameObject* go);
	void SortGos();

	//0816, ������, �����̵� ��ȯ �Լ�
	SceneId GetSceneId();
	//
	sf::View& GetWorldView() { return worldView; }
	sf::View& GetUiView() { return uiView; }
	sf::Vector2f ScreenToWorldPos(sf::Vector2f screenPos);
	sf::Vector2f ScreenToUiPos(sf::Vector2f screenPos);
	sf::Vector2f WorldPosToScreen(sf::Vector2f worldPos);
	sf::Vector2f UiPosPosToScreen(sf::Vector2f uiPos);

	virtual void Init() = 0;
	virtual void Release() = 0;

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

};

