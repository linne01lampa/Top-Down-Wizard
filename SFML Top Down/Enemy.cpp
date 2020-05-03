#include "Enemy.h"
#include <cmath>	
#include <iostream>
Enemy::Enemy()
{
	myShape.setFillColor(sf::Color::Black);
	myShape.setRadius(50.f);
	myShape.setPosition(300, 500);
	mySpeed = 50.f;
	//myPlayer = aPlayer;
	reloaded = true;
	myTimer = 0;
	myTimerSpeed = .2f;
}

Enemy::~Enemy()
{
}

void Enemy::Init(Player &aPlayer)
{
	myShape.setFillColor(sf::Color::Black);
	myShape.setRadius(50.f);
	myShape.setPosition(300, 500);
	mySpeed = 50.f;
	myPlayer = &aPlayer;
	reloaded = true;
	myTimer = 0;
	myTimerSpeed = .2f;
}

void Enemy::Update(const float& someDelta, sf::RenderWindow& aWindow)
{
	myRect = myShape.getGlobalBounds();
	myCenter = sf::Vector2f((myShape.getPosition().x + myShape.getGlobalBounds().width * .5f), (myShape.getPosition().y + myShape.getGlobalBounds().height * .5f));
	myTimer += someDelta;
	if (myTimer > myTimerSpeed)
	{
		reloaded = true;
	}

	for (size_t i = 0; i < myBullets.size(); i++)
	{
		myBullets[i].Update(someDelta);

		if (myBullets[i].myBullet.getPosition().x < 0 || myBullets[i].myBullet.getPosition().x > aWindow.getSize().x || myBullets[i].myBullet.getPosition().y < 0 || myBullets[i].myBullet.getPosition().y > aWindow.getSize().y)
		{
			myBullets.erase(myBullets.begin() + i);
		}

		if (myBullets[i].myRect.intersects(myPlayer->myRect))
		{
			myBullets.erase(myBullets.begin() + i);
			std::cout << "COLLIDE" << std::endl;
		}
	}
	Fire();
}

void Enemy::Draw(sf::RenderWindow &aWindow)
{
	aWindow.draw(myShape);
	for (size_t i = 0; i < myBullets.size(); i++)
	{
		aWindow.draw(myBullets[i].myBullet);
	}
}

void Enemy::Fire()
{
	float distance = std::sqrt((std::abs(((myPlayer->myCenter.x - myCenter.x) * (myPlayer->myCenter.x - myCenter.x) + (myPlayer->myCenter.y - myCenter.y) * (myPlayer->myCenter.y - myCenter.y)))));
	sf::Vector2f aim = myPlayer->myCenter - myCenter;
	sf::Vector2f norm = aim / sqrt(pow(aim.x, 2) + pow(aim.y, 2));

	if (distance < 500)
	{
		myBullets.push_back(Bullet(norm, 1000.f, myCenter));
		myTimer = 0;
	}
}
