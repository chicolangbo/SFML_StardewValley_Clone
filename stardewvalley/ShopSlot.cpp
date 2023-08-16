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
    itemIcon.Setting(item->resource, item->name, item->nickName);
}

ShopSlot::~ShopSlot()
{
}

void ShopSlot::Init()
{
    UiButton::Init();
}

void ShopSlot::Release()
{
    UiButton::Release();
}

void ShopSlot::Reset()
{
    UiButton::Reset();
}

void ShopSlot::Update(float dt)
{
    UiButton::Update(dt);
}

void ShopSlot::Draw(sf::RenderWindow& window)
{
    UiButton::Draw(window);
}