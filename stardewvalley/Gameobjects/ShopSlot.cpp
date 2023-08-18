#include "stdafx.h"
#include "ShopSlot.h"
#include "DataTableMgr.h"
#include "AllItemTable.h"
#include "DataTable.h"

ShopSlot::ShopSlot(ItemId id, const std::string& textureId, const std::string& n, sf::Rect<float> centerRect, sf::Rect<float> size, int vc, const std::string& nickName)
    : UiButton(),
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
    //iconCell.SetPosition(cellBox.GetPosition().x + iconCell.sprite.getGlobalBounds().width, cellBox.GetPosition().y);
    itemIcon.SetPosition(iconCell.GetPosition());
    itemText.SetPosition(cellBox.GetPosition().x, cellBox.GetPosition().y);
    coin.SetPosition(cellBox.GetPosition().x, cellBox.GetPosition().y);
    coinText.SetPosition(coin.GetPosition());
}

void ShopSlot::Init()
{
    UiButton::Init();
    cellBox.Init();
}

void ShopSlot::Release()
{
    UiButton::Release();
}

void ShopSlot::Reset()
{
    // RESOURCE LOAD
    UiButton::Reset(); 
    iconCell.Reset();
    itemIcon.Reset();
    itemText.Reset();
    coin.Reset();
    coinText.Reset();

    // ORIGIN, SCALE
    iconCell.SetOrigin(Origins::MC);
    iconCell.SetScale(1.f, 1.f);
    
    itemIcon.SetOrigin(Origins::MC);
    itemIcon.SetScale(4.5f, 4.5f);

    wstring name = DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem)->GetUniName(id);
    itemText.SetText(name, 50, sf::Color::Black, Origins::TL, 100, position.x, position.y);

    coin.SetOrigin(Origins::TR);
    coin.SetScale(3.f, 3.f);

    int price = DATATABLE_MGR.Get<AllItemTable>(DataTable::Ids::AllItem)->Get(id)->price;
    coinText.SetOrigin(Origins::TL);
    coinText.SetText(to_string(price), 50, sf::Color::Black, Origins::TL, 100, position.x, position.y);
}

void ShopSlot::Update(float dt)
{
    UiButton::Update(dt);
}

void ShopSlot::Draw(sf::RenderWindow& window)
{
    UiButton::Draw(window);
    iconCell.Draw(window);
    itemIcon.Draw(window);
    itemText.Draw(window);
    coin.Draw(window);
    coinText.Draw(window);
    cellBox.Draw(window);
}