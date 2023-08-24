#include "stdafx.h"
#include "Tree.h"
#include "Objects.h"
#include "ResourceMgr.h"
#include "Utils.h"
#include "InputMgr.h"

Tree::Tree(const std::string& name, const std::string& branchId, const std::string& stumpId,
	const std::string& branchNick, const std::string& stumpNick) : GameObject(name)
{
	stump = new Objects(stumpId, "stump", "stump");
	this->branchId = branchId;
	this->branchNick = branchNick;
}

Tree::~Tree()
{
	delete stump;
}

void Tree::Init()
{
	stump->Init();
}

void Tree::Release()
{
}

void Tree::Reset()
{
	stump->Reset();

	branch.setScale({ 4.5f, 4.5f });
	branch.setTexture(*RESOURCE_MGR.GetTexture(branchId));
	sf::IntRect texRect = RESOURCE_MGR.GetTextureRect(branchNick);
	branch.setTextureRect(texRect);
	Utils::SetOrigin(branch, Origins::BC);
	branch.setPosition(stump->GetPosition().x + 36, stump->GetPosition().y + 15);

	hitbox.setSize({ branch.getGlobalBounds().width, branch.getGlobalBounds().height });
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2.f);
	Utils::SetOrigin(hitbox, Origins::BC);
	hitbox.setPosition(branch.getPosition());
}

void Tree::Update(float dt)
{
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num0))
	{
		stump->colliderOnOff = !(stump->colliderOnOff);
	}

	if (hit)
	{
		time += dt;
		if (shake >= 0.1f)
		{
			direction = -1.f;
		}
		else if (shake <= -0.1f)
		{
			direction = 1.f;
		}

		shake += dt * direction;
		branch.rotate(shake);
		if (time >= 0.5f)
		{
			hit = false;
			time = 0;
		}
	}

	if (treeRotation)
	{
		rotation += dt * 0.1f;
		branch.rotate(rotation);
		time += dt;
		if (time >= 1.6f)
		{
			fallingTree = true;
		}
	}
}

void Tree::Draw(sf::RenderWindow& window)
{
	stump->Draw(window);
	if (!fallingTree)
	{
		window.draw(branch);
	}
	//window.draw(hitbox);
}

void Tree::SetPosition(const sf::Vector2f& p)
{
	GameObject::SetPosition(p);
	branch.setPosition(p);
	stump->SetPosition(p);
	hitbox.setPosition(p);
}

void Tree::SetPosition(float x, float y)
{
	GameObject::SetPosition(x, y);
	branch.setPosition(x, y);
	stump->SetPosition(x, y);
	hitbox.setPosition(x, y);
}

void Tree::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(branch, origin);
		stump->SetOrigin(origin);
		Utils::SetOrigin(hitbox, origin);
	}
}

void Tree::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	branch.setOrigin(x, y);
	stump->SetOrigin(x, y);
	hitbox.setOrigin(x, y);
}

sf::RectangleShape Tree::GetHitbox()
{
	return hitbox;
}
