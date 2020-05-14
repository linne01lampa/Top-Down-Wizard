#include "App.h"
//#include <math.h>
#include <cmath>

App::App(sf::RenderWindow &aWindow)
{
	myTexture.loadFromFile("hat.png");
	myPlayer.Init(myTexture);
	myTileMap.Init();
	//myEnemy.Init(myPlayer);
	App::myTimer = 0;
	myBoxes.push_back(Box());
	myBoxes[0].Init(myPlayer);
	//myEnemies[0].Init(myPlayer);
	myEnemies.push_back(Enemy(myPlayer));
	myTimer = 0;
	App::special = false;
	myFont.loadFromFile(("Baloo.ttf"));
	myTextE.setFont(myFont);
	myTextE.setString("Press E to pickup!");
	myTextE.setCharacterSize(24);
	myTextE.setFillColor(sf::Color::Red);
	my2ndAttack.setFont(myFont);
	my2ndAttack.setString("SUPER ATTACK AVAILABLE");
	my2ndAttack.setCharacterSize(24);
	my2ndAttack.setFillColor(sf::Color::Red);
	my2ndAttack.setPosition(aWindow.getSize().x / 2, 20);
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

	for (size_t i = 0; i < myTileMap.myWalls.size(); i++)
	{
		if (myPlayer.myRect.intersects(myTileMap.myWalls[i].getGlobalBounds()))
		{
			//HÄR SKA DEN VÄL COLLIDA?????????????????
			myPlayer.MoveToLastPos();
		}
	}

	
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
		mySpecialBullets.push_back(Bullet(myNorm, 1000.f, myPlayer.myCenter));
		mySpecialBullets.back().myBullet.setFillColor(sf::Color(255, 0, 0, 255));
		mySpecialBullets.back().myBullet.setScale(2.f,2.f);
		
		auto& trail = mySpecialBullets.back().myTrail;
		trail.SetColor(sf::Color(255, 100, 0, 255));
		trail.SetOffset(15.f);
		trail.SetWidth(10.f, 32.f);
		trail.SetMinDistance(50.f);
		trail.SetLifetime(0.7f);
	}

	for (size_t i = 0; i < mySpecialBullets.size(); i++)
	{
		mySpecialBullets[i].Update(someDelta);
		if (mySpecialBullets[i].myBullet.getPosition().x < 0 || mySpecialBullets[i].myBullet.getPosition().x > aWindow.getSize().x
			|| mySpecialBullets[i].myBullet.getPosition().y < 0 || mySpecialBullets[i].myBullet.getPosition().y > aWindow.getSize().y)
		{
			mySpecialBullets.erase(mySpecialBullets.begin() + i);
			break;
		}
		for (size_t l = 0; l < myEnemies.size(); l++)
		{
			if (mySpecialBullets[i].myRect.intersects(myEnemies[0].myRect))
			{
				mySpecialBullets.erase(mySpecialBullets.begin() + i);
				myEnemies[0].myHealth -= 2;
				if (myEnemies[0].myHealth <= 0)
				{
					myEnemies.erase(myEnemies.begin() + l);
				}
			}
		}
	}
	myTextE.setPosition(myPlayer.myCenter.x - (myTextE.getLocalBounds().width / 2), myPlayer.myCenter.y - 75.f);

	for (size_t i = 0; i < myBoxes.size(); i++)
	{
		if (myBoxes[i].GetPickable() && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			special = true;
			myBoxes.erase(myBoxes.begin() + i);
		}
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
	for (auto& enemy : myEnemies)
	{
		enemy.Update(someDelta, aWindow);
	}
	for (auto& box : myBoxes)
	{
		box.Update(someDelta, aWindow);
	}
	myPlayer.Update(someDelta, aWindow);
}

void App::Draw(sf::RenderWindow& aWindow)
{
	myTileMap.Draw(aWindow);
	for (auto& myEnemies : myEnemies)
	{
		myEnemies.Draw(aWindow);
	}
	for (auto& i : mySpecialBullets)
	{
		i.Draw(aWindow);
	}
	myPlayer.Draw(aWindow);
	for (auto& box : myBoxes)
	{
		box.Draw(aWindow);
	}
	for (auto& myBullet : myBullets)
	{
		aWindow.draw(myBullet.myTrail);
		aWindow.draw(myBullet.myBullet);
	}

	if (special)
	{
		aWindow.draw(my2ndAttack);
	}

	for (auto& box : myBoxes)
	{
		if (box.GetPickable())
		{
			aWindow.draw(myTextE);
		}
	}
}


