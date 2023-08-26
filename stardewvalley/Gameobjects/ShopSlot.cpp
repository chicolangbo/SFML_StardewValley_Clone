#include "stdafx.h"
#include "ShopSlot.h"
#include "DataTableMgr.h"
#include "AllItemTable.h"
#include "DataTable.h"
#include "InputMgr.h"
#include "SceneMgr.h"

ShopSlot::ShopSlot(ItemId id, const std::string& textureId, const std::string& n, sf::Rect<float> centerRect, sf::Rect<float> size, int vc, const std::string& nickName)
    : GameObject(n),
    id(id),
    cellBox(textureId, n, centerRect, size, vc),
    iconCell("graphics/MenuTiles.png", "invenCell", "invenCell"),
    itemText("itemText", "fonts/SDMiSaeng.ttf"),
    coin("graphics/Cursors.ko-KR.png", "coin", "coin"),
    coinText("coinText", "fonts/SDMiSaeng.ttf")
{
    const ItemInfo* item = DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem)->Get(id);
    itemIcon.Setting(item->resource, item->name_e, item->nickName);
}

ShopSlot::~ShopSlot()
{
}

void ShopSlot::SetOrigin(Origins o)
{
    cellBox.SetOrigin(o);
}

void ShopSlot::SetPosition(float x, float y)
{
    cellBox.SetPosition(x, y);
    iconCell.SetPosition(cellBox.GetPosition().x + iconCell.sprite.getGlobalBounds().width, (cellBox.GetPosition().y + cellBox.GetSize().y/2.f));
    itemIcon.SetPosition(iconCell.GetPosition());
    itemText.SetPosition(itemIcon.GetPosition().x + 100.f, itemIcon.GetPosition().y - 20.f);
    coin.SetPosition(cellBox.GetPosition().x + cellBox.GetSize().x - 50.f, itemIcon.GetPosition().y);
    coinText.SetPosition(coin.GetPosition().x - 50.f, itemText.GetPosition().y - 10.f);
}

void ShopSlot::Init()
{
    cellBox.Init();
}

void ShopSlot::Release()
{
}

void ShopSlot::Reset()
{
    // RESOURCE LOAD
    iconCell.Reset();
    itemIcon.Reset();
    itemText.Reset();
    coin.Reset();
    coinText.Reset();

    // ORIGIN, SCALE
    iconCell.SetOrigin(Origins::MC);
    iconCell.SetScale(1.f, 1.f);
    iconCell.colliderOnOff = false;
    
    itemIcon.SetOrigin(Origins::MC);
    itemIcon.SetScale(5.f, 5.f);
    itemIcon.colliderOnOff = false;

    if (Variables::CurrentLang == Languages::ENG)
    {
        itemText.SetString(DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem)->GetName(id));
    }
    else
    {
        itemText.text.setString(DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem)->GetUniName(id));
    }
    itemText.text.setCharacterSize(70);
    itemText.text.setFillColor(sf::Color::Black);
    itemText.SetOrigin(Origins::ML);
    itemText.SetPosition(position.x, position.y);

    coin.SetOrigin(Origins::MC);
    coin.SetScale(6.f, 6.f);
    coin.colliderOnOff = false;

    int price = DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem)->Get(id)->price;
    coinText.SetText(to_string(price), 70, sf::Color::Black, Origins::MR, 100, position.x, position.y);

	isHover = false;
}

void ShopSlot::Update(float dt)
{
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

	bool prevHover = isHover;
	isHover = cellBox.vertexArray[0].position.x <= uiMousePos.x && cellBox.vertexArray[9].position.x >= uiMousePos.x && cellBox.vertexArray[0].position.y <= uiMousePos.y && cellBox.vertexArray[35].position.y >= uiMousePos.y;

	if (this->GetActive())
	{
		if (!prevHover && isHover)
		{
			if (OnEnter != nullptr)
			{
				OnEnter();
			}
		}
		if (prevHover && !isHover)
		{
			if (OnExit != nullptr)
			{
				OnExit();
			}
		}
		if (isHover && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			if (OnClick != nullptr)
			{
				OnClick();
			}
		}
	}
}

void ShopSlot::Draw(sf::RenderWindow& window)
{
    cellBox.Draw(window);
    iconCell.Draw(window);
    itemIcon.Draw(window);
    itemText.Draw(window);
    coin.Draw(window);
    coinText.Draw(window);
}