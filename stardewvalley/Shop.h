#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "SliceImageGo.h"
#include "UiButton.h"
#include "TextGo.h"
#include "Player2.h"
#include "Inventory.h"

class Shop :
    public GameObject
{
protected:
    Player2* player;
    Inventory* inven;

    // SHOP SLOT VECTOR

    // UI
    SpriteGo pierre;
    TextGo pierreText;
    SliceImageGo pierreTextBox;
    
    SliceImageGo shopBox;
    

    UiButton xButton;
    SliceImageGo invenBox;
    SliceImageGo textBox;



public:

};

