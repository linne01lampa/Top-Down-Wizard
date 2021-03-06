#include "Enemy.h"
#include <cmath>
#include <iostream>
Enemy::Enemy()
{
	myShape.setFillColor(sf::Color::Black);
	myShape.setRadius(50.f);
	myShape.setPosition(300, 500);
	mySpeed = 50.f;
	//myPlayer = &aPlayer;
	reloaded = true;
	myTimer = 0;
	myTimerSpeed = .2f;
	myHealth = 5;
}

Enemy::Enemy(Player& aPlayer, sf::Vector2f aPosition, std::vector<sf::Sprite> someWalls, bool aBig)
{
	if (!aBig)
	{
		myShape.setFillColor(sf::Color::Black);
		myShape.setRadius(20.f);
		//myShape.setPosition(375, 600);
		myShape.setPosition(aPosition);
		mySpeed = 50.f;
		myPlayer = &aPlayer;
		reloaded = true;
		myTimer = 0;
		myTimerSpeed = .2f;
		myHealth = 5;
		myWalls = someWalls;
	}
	else
	{
		myShape.setFillColor(sf::Color::Red);
		myShape.setRadius(100.f);
		//myShape.setPosition(375, 600);
		myShape.setPosition(aPosition);
		mySpeed = 50.f;
		myPlayer = &aPlayer;
		reloaded = true;
		myTimer = 0;
		myTimerSpeed = .15f;
		myHealth = 25;
		myWalls = someWalls;
	}
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
	myHealth = 5;
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

		if (myBullets[i].myBullet.getPosition().x < 0 || myBullets[i].myBullet.getPosition().x > aWindow.getSize().x
			|| myBullets[i].myBullet.getPosition().y < 0 || myBullets[i].myBullet.getPosition().y > aWindow.getSize().y)
		{
			myBullets.erase(myBullets.begin() + i);
			break;
		}
		else if (myBullets[i].myRect.intersects(myPlayer->myRect))
		{
			myBullets.erase(myBullets.begin() + i);
			myPlayer->Damage(-1);
			break;
		}

		for (size_t l = 0; l < myWalls.size(); l++)
		{
			if (myBullets[i].myRect.intersects(myWalls[l].getGlobalBounds()))
			{
				myBullets.erase(myBullets.begin() + i);
				break;
			}
		}
	}
	Fire();
}

void Enemy::Draw(sf::RenderWindow &aWindow)
{
	aWindow.draw(myShape);
	for (size_t i = 0; i < myBullets.size(); i++)
	{
		aWindow.draw(myBullets[i].myTrail);
		aWindow.draw(myBullets[i].myBullet);
	}
}

void Enemy::Fire()
{
	float distance = std::sqrt((std::abs(((myPlayer->myCenter.x - myCenter.x) * (myPlayer->myCenter.x - myCenter.x) + (myPlayer->myCenter.y - myCenter.y) * (myPlayer->myCenter.y - myCenter.y)))));
	sf::Vector2f aim = myPlayer->myCenter - myCenter;
	sf::Vector2f norm = aim / sqrt(pow(aim.x, 2) + pow(aim.y, 2));

	if (distance < 500 && reloaded)
	{
		myBullets.push_back(Bullet(norm, 1000.f, myCenter));

		auto& trail = myBullets.back().myTrail;
		trail.SetColor(sf::Color::Red);
		trail.SetLifetime(0.2f);
		myTimer = 0;
		reloaded = false;
	}
}
