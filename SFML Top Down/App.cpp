#include "App.h"
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>

App::App()
{
	myTexture.loadFromFile("hat.png");
	myPlayer.Init(myTexture);
	myTileMap.Init();
	myEnemy.Init(myPlayer);
	App::myTimer = 0;
}


App::~App()
{
}

void App::Update(const float& someDelta, sf::RenderWindow &aWindow)
{
	myTimer += someDelta;
	myMousePos = sf::Vector2f(sf::Mouse::getPosition(aWindow));
	myAim = myMousePos - myPlayer.myCenter;
	myNorm = myAim / sqrt(pow(myAim.x,2) + pow(myAim.y,2));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && myTimer >= myTimerSpeed)
	{
		myBullets.push_back(Bullet(myNorm, 1000.f, myPlayer.myCenter));

		myBullets.back().myBullet.setFillColor(sf::Color(255, 0, 255, 255));

		auto& trail = myBullets.back().myTrail;
		trail.SetColor(sf::Color(255, 0, 255, 255));
		trail.SetOffset(15.f);
		trail.SetWidth(5.f, 16.f);
		trail.SetMinDistance(50.f);
		trail.SetLifetime(0.4f);

		myTimer = 0;
	}

	//std::cout << myBullets.size() << "\n";

	for (size_t i = 0; i < myBullets.size(); i++)
	{
		myBullets[i].Update(someDelta);

		if (myBullets[i].myBullet.getPosition().x < 0 || myBullets[i].myBullet.getPosition().x > aWindow.getSize().x || myBullets[i].myBullet.getPosition().y < 0 || myBullets[i].myBullet.getPosition().y > aWindow.getSize().y)
		{
			myBullets.erase(myBullets.begin() + i);
		}
	}

	myEnemy.Update(someDelta, aWindow);
	myPlayer.Update(someDelta, aWindow);
}

void App::Draw(sf::RenderWindow& aWindow)
{
	myTileMap.Draw(aWindow);
	myEnemy.Draw(aWindow);
	myPlayer.Draw(aWindow);
	for (size_t i = 0; i < myBullets.size(); i++)
	{
		aWindow.draw(myBullets[i].myTrail);
		aWindow.draw(myBullets[i].myBullet);
	}

}