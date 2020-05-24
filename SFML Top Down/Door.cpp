#include "Door.h"

Door::Door()
{
}

Door::~Door()
{
}

void Door::Init(Player& aPlayer)
{
	myPlayer = &aPlayer;
	myShape.setPosition(1160, 640);
	myShape.setFillColor(sf::Color::Green);
	myShape.setOutlineColor(sf::Color::Yellow);
	myShape.setSize(sf::Vector2f(25, 50));
	myNextLevel = false;
}

void Door::Update(const float& someDelta, sf::RenderWindow& aWindow)
{
	myRect = myShape.getGlobalBounds();

	if (myRect.intersects(myPlayer->myRect))
	{
		myNextLevel = true;
	}
}

void Door::Draw(sf::RenderWindow& aWindow)
{
	aWindow.draw(myShape);
}
