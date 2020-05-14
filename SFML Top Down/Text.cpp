#include "Text.h"

Text::Text()
{
	myWrittenText.setPosition(100, 100);
}

Text::~Text()
{
}

void Text::Init(sf::Font aFont)
{
	myWrittenText.setPosition(100, 100);
	myWrittenText.setFont(aFont);
	myText = "HEJ HUR FAN MÅR DU?";
}

void Text::Update(const float& someDelta, sf::RenderWindow& aWindow)
{
	if (myTimer.getElapsedTime().asSeconds() > 0.1f && myCharacters < myText.length())
	{
		myTimer.restart();
		myCharacters++;
		myWrittenText.setString(myText.substr(0, myCharacters));
	}
}

void Text::Draw(sf::RenderWindow& aWindow)
{
	aWindow.draw(myWrittenText);
}
