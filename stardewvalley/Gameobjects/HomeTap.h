#pragma once
#include "GameObject.h"
#include "SliceImageGo.h"
#include "TextGo.h"
#include "RectButton.h"

class Player2;
class SpriteGo;

class HomeTap :
    public GameObject
{
protected:
    Player2* player = nullptr;
    SpriteGo* bedding = nullptr;
    
    std::list<GameObject*> homeUiObjects;

    SliceImageGo box;
    TextGo question;
    RectButton yes;
    RectButton no;

public:
    bool homeTapOn = false;

    HomeTap(const std::string& n = "");
    virtual ~HomeTap() override;

    GameObject* AddUi(GameObject* go);
    bool Exist(GameObject* go);

    virtual void Init() override;
    virtual void Reset() override;
    virtual void Release() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    void SortGos();
    void SetPlayer(Player2* p) { player = p; }
    void SetBedding(SpriteGo* b) { bedding = b; }

    void TapOnOff();
    void ButtonSetUp();
};

