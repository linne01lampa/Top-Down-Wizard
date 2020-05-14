#include "Player.h"

Player::Player()
{
	//mySprite.setTexture(aTexture);
	//mySprite.setTextureRect(sf::IntRect(0, 0, 64, 64));		
	//mySprite.setRadius(20.f);
	mySprite.setColor(sf::Color(255, 255, 255, 255));
	mySprite.setScale(.15f, .15f);
	mySpeed = 500.f;
}

Player::~Player()
{

}

void Player::Init(const sf::Texture& aTexture)
{
	mySprite.setTexture(aTexture);
	//mySprite.setTexture(aTexture);
	//mySprite.setTextureRect(sf::IntRect(0, 0, 64, 64));		
	//mySprite.setRadius(20.f);
	mySprite.setColor(sf::Color(255, 255, 255, 255));
	mySprite.setScale(.15f, .15f);
	mySpeed = 500.f;
}

void Player::Update(const float& someDelta, sf::RenderWindow &aWindow)
{
	myRect = mySprite.getGlobalBounds();
	myCenter = sf::Vector2f((mySprite.getPosition().x + mySprite.getGlobalBounds().width * .5f), (mySprite.getPosition().y + mySprite.getGlobalBounds().height * .5f));
	myLastPos = mySprite.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mySprite.getPosition().x > 0)
	{
		mySprite.move(-mySpeed * someDelta, 0);
		dir = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && mySprite.getPosition().x < aWindow.getSize().x - mySprite.getLocalBounds().width * mySprite.getScale().x)
	{
		mySprite.move(mySpeed * someDelta, 0);
		dir = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mySprite.getPosition().y > 0)
	{
		mySprite.move(0, -mySpeed * someDelta);
		dir = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mySprite.getPosition().y < aWindow.getSize().y - mySprite.getLocalBounds().height * mySprite.getScale().y)
	{
		mySprite.move(0, mySpeed * someDelta);
		dir = 3;
	}
}

void Player::Draw(sf::RenderWindow& aWindow)
{
	aWindow.draw(mySprite);
}

void Player::MoveToLastPos()
{
	if (dir == 0)
	{
		myLastPos.x += 2;
	}
	if (dir == 1)
	{
		myLastPos.x -= 2;
	}
	if (dir == 2)
	{
		myLastPos.y += 2;
	}
	if (dir == 3)
	{
		myLastPos.y -= 2;
	}
	mySprite.setPosition(myLastPos);
}

