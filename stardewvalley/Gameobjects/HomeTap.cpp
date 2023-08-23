#include "stdafx.h"
#include "HomeTap.h"
#include "Framework.h"
#include "DataTableMgr.h"
#include "StringTable.h"

HomeTap::HomeTap(const std::string& n)
    :GameObject(n),
    box("graphics/box1.png", "box", { 22,27,36,31 }, { 0,0,80,80 }, NINE_SLICE),
    question("question", "fonts/SDMiSaeng.ttf"),
    yes("fonts/SDMiSaeng.ttf", sf::Vector2f(0.f, 0.f), "yes"),
    no("fonts/SDMiSaeng.ttf", sf::Vector2f(0.f, 0.f), "no")
{
    AddUi(&box);
    AddUi(&question);
    AddUi(&yes);
    AddUi(&no);
}

HomeTap::~HomeTap()
{
    Release();
}

GameObject* HomeTap::AddUi(GameObject* go)
{
    if (!Exist(go))
    {
        homeUiObjects.push_back(go);
    }
    return go;
}

bool HomeTap::Exist(GameObject* go)
{
    for (auto& m : homeUiObjects)
    {
        if (m == go)
        {
            return true;
        }
    }
    return false;
}

void HomeTap::Init()
{
    for (auto i : homeUiObjects)
    {
        i->Init();
    }
    ButtonSetUp();
    TapOnOff();
}

void HomeTap::Reset()
{
    for (auto i : homeUiObjects)
    {
        i->Reset();
    }

    sf::Vector2f size = FRAMEWORK.GetWindowSize();

    box.SetSize({ size.x, size.y / 3.f });
    box.SetOrigin(Origins::BL);
    box.SetPosition(0, size.y);

    StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);
    float border = 25.f;

    question.SetText(stringTable->GetUni("SAVE_Q", Languages::KOR), 70, sf::Color::Black, Origins::TL, 101, box.GetPosition().x + border*2, box.GetPosition().y - box.GetSize().y + border);

    yes.text.setString(stringTable->GetUni("SAVE_YES", Languages::KOR));
    yes.text.setCharacterSize(70);
    yes.text.setFillColor(sf::Color::Black);
    yes.SetSize(box.GetSize().x - border*2.f, box.GetSize().y / 3.f - border);
    yes.SetOrigin(Origins::BL);
    yes.SetPosition(border, size.y - border -  yes.rectangle.getSize().y - 10.f);
    yes.text.setPosition(yes.GetPosition().x + border, yes.GetPosition().y - yes.text.getCharacterSize());
    yes.rectangle.setOutlineThickness(5);

    no.text.setString(stringTable->GetUni("SAVE_UNDO", Languages::KOR));
    no.text.setCharacterSize(70);
    no.text.setFillColor(sf::Color::Black);
    no.SetSize(box.GetSize().x - border*2.f, box.GetSize().y / 3.f - border);
    no.SetOrigin(Origins::BL);
    no.SetPosition(border, size.y - border);
    no.text.setPosition(no.GetPosition().x + border, no.GetPosition().y - no.text.getCharacterSize());
    no.rectangle.setOutlineThickness(5);
}

void HomeTap::Release()
{
    homeUiObjects.clear();
}

void HomeTap::Update(float dt)
{
    for (auto i : homeUiObjects)
    {
        i->Update(dt);
    }
}

void HomeTap::Draw(sf::RenderWindow& window)
{
    SortGos();

    for (auto m : homeUiObjects)
    {
        if (m->GetActive())
        {
            m->Draw(window);
        }
    }
}

void HomeTap::SortGos()
{
    homeUiObjects.sort([](GameObject* lhs, GameObject* rhs) {
        if (lhs->sortLayer != rhs->sortLayer)
            return lhs->sortLayer < rhs->sortLayer;
        return lhs->sortOrder < rhs->sortOrder;
        });
}

void HomeTap::TapOnOff()
{
    if (homeTapOn)
    {
        for (auto i : homeUiObjects)
        {
            i->SetActive(true);
        }
    }

    else
    {
        for (auto i : homeUiObjects)
        {
            i->SetActive(false);
        }
    }
}

void HomeTap::ButtonSetUp()
{
    yes.OnClick = [this]() {
        save = true;
        homeTapOn = false;
        TapOnOff();
    };
    yes.OnEnter = [this]() {
        // 빨간색 라인
        yes.rectangle.setOutlineColor(sf::Color::Red);
    };
    yes.OnExit = [this]() {
        // 라인 없애기
        yes.rectangle.setOutlineColor(sf::Color::Transparent);
    };

    no.OnClick = [this]() {
        // 그냥 창 닫기
        homeTapOn = false;
        TapOnOff();
    };
    no.OnEnter = [this]() {
        // 빨간색 라인
        no.rectangle.setOutlineColor(sf::Color::Red);
    };
    no.OnExit = [this]() {
        // 라인 없애기
        no.rectangle.setOutlineColor(sf::Color::Transparent);
    };
}
