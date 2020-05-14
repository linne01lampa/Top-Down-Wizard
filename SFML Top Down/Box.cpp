#include "Box.h"

Box::Box()
{
	myShape.setPosition(100, 100);
	myShape.setFillColor(sf::Color(139, 69, 19));
	myShape.setOutlineColor(sf::Color::Yellow);
	myShape.setSize(sf::Vector2f(25, 25));
	myPlayer = new Player();
	pickable = false;
}

Box::~Box()
{
}

void Box::Init(Player &aPlayer)
{
	myShape.setPosition(100, 100);
	myShape.setFillColor(sf::Color(139, 69, 19));
	myShape.setOutlineColor(sf::Color::Yellow);
	myShape.setSize(sf::Vector2f(25, 25));
	myPlayer = &aPlayer;
	pickable = false;
}

void Box::Update(const float& someDelta, sf::RenderWindow& aWindow)
{
	myRect = myShape.getGlobalBounds();

	if (myRect.intersects(myPlayer->myRect))
	{
		pickable = true;
		myShape.setOutlineThickness(5.f);
	}
	else
	{
		pickable = false;
		myShape.setOutlineThickness(0.f);
	}
}

void Box::Draw(sf::RenderWindow& aWindow)
{
	aWindow.draw(myShape);
}

bool Box::GetPickable()
{
	return pickable;
}
