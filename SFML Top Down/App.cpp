#include "App.h"
//#include <math.h>
#include <cmath>

App::App()
{
	myTexture.loadFromFile("hat.png");
	myPlayer.Init(myTexture);
	myTileMap.Init();
	//myEnemy.Init(myPlayer);
	App::myTimer = 0;
	myBox.Init(myPlayer);
	//myEnemies[0].Init(myPlayer);
	myEnemies.push_back(Enemy(myPlayer));
	myTimer = 0;
	App::special = false;
	myFont.loadFromFile(("Baloo.ttf"));
	myTextE.setFont(myFont);
	myTextE.setString("Press E to pickup!");
	myTextE.setCharacterSize(24);
	myTextE.setFillColor(sf::Color::Red);
}


App::~App()
{
}

void App::Update(const float& someDelta, sf::RenderWindow& aWindow)
{
	myTimer += someDelta;
	myMousePos = sf::Vector2f(sf::Mouse::getPosition(aWindow));
	myAim = myMousePos - myPlayer.myCenter;
	myNorm = myAim / sqrt(pow(myAim.x, 2) + pow(myAim.y, 2));

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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && special)
	{
		//std::cout << "YEET" << std::endl;
		special = false;
		mySpecialBullet.push_back(Bullet(myNorm, 1000.f, myPlayer.myCenter));
		mySpecialBullet.back().myBullet.setFillColor(sf::Color(255, 0, 0, 255));
		mySpecialBullet.back().myBullet.setScale(2.f,2.f);
		
		auto& trail = mySpecialBullet.back().myTrail;
		trail.SetColor(sf::Color(255, 100, 0, 255));
		trail.SetOffset(15.f);
		trail.SetWidth(10.f, 32.f);
		trail.SetMinDistance(50.f);
		trail.SetLifetime(0.7f);
	}

	for (size_t i = 0; i < mySpecialBullet.size(); i++)
	{
		mySpecialBullet[i].Update(someDelta);
		if (mySpecialBullet[i].myBullet.getPosition().x < 0 || mySpecialBullet[i].myBullet.getPosition().x > aWindow.getSize().x
			|| mySpecialBullet[i].myBullet.getPosition().y < 0 || mySpecialBullet[i].myBullet.getPosition().y > aWindow.getSize().y)
		{
			mySpecialBullet.erase(mySpecialBullet.begin() + i);
			break;
		}
		for (size_t l = 0; l < myEnemies.size(); l++)
		{
			if (mySpecialBullet[i].myRect.intersects(myEnemies[0].myRect))
			{
				mySpecialBullet.erase(mySpecialBullet.begin() + i);
				myEnemies[0].myHealth -= 2;
				if (myEnemies[0].myHealth <= 0)
				{
					myEnemies.erase(myEnemies.begin() + l);
				}
			}
		}
	}
	myTextE.setPosition(myPlayer.myCenter.x - (myTextE.getLocalBounds().width / 2), myPlayer.myCenter.y - 75.f);
	
	if (myBox.GetPickable() && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		special = true;
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
		for (size_t l = 0; l < myEnemies.size(); l++)
		{
			if (myBullets[i].myRect.intersects(myEnemies[0].myRect))
			{
				myBullets.erase(myBullets.begin() + i);
				myEnemies[0].myHealth--;
				if (myEnemies[0].myHealth <= 0)
				{
					myEnemies.erase(myEnemies.begin() + l);
				}
			}
		}
	}
	for (size_t i = 0; i < myEnemies.size(); i++)
	{
		myEnemies[i].Update(someDelta, aWindow);
	}
	myBox.Update(someDelta, aWindow);
	myPlayer.Update(someDelta, aWindow);
}

void App::Draw(sf::RenderWindow& aWindow)
{
	myTileMap.Draw(aWindow);
	for (auto& myEnemies : myEnemies)
	{
		myEnemies.Draw(aWindow);
	}
	for (auto& i : mySpecialBullet)
	{
		i.Draw(aWindow);
	}
	myPlayer.Draw(aWindow);
	myBox.Draw(aWindow);
	for (auto& myBullet : myBullets)
	{
		aWindow.draw(myBullet.myTrail);
		aWindow.draw(myBullet.myBullet);
	}

	if (myBox.GetPickable())
	{
		aWindow.draw(myTextE);
	}
}
