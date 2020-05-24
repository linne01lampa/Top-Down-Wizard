#include "App.h"
//#include <math.h>
#include <cmath>
#include <random>

App::App(sf::RenderWindow &aWindow)
{
	myTexture.loadFromFile("hat.png");
	myFont.loadFromFile(("Baloo.ttf"));
	myGroundTex.loadFromFile("tileset.png");
	//myPlayer.Init(myTexture, myFont);
	//myTileMap.Init();
	//myDoor.Init(myPlayer);
	////myEnemy.Init(myPlayer);
	//App::myTimer = 0;
	//myBoxes.push_back(Box());
	//myBoxes[0].Init(myPlayer);
	////myEnemies[0].Init(myPlayer);
	//myEnemies.push_back(Enemy(myPlayer));
	//myTimer = 0;
	//App::mySpecial = false;
	LoadLevel(0);
	myTextE.setFont(myFont);
	myTextE.setString("Press E to pickup!");
	myTextE.setCharacterSize(24);
	myTextE.setFillColor(sf::Color::Black);
	my2ndAttack.setFont(myFont);
	my2ndAttack.setString("SUPER ATTACK AVAILABLE");
	my2ndAttack.setCharacterSize(24);
	my2ndAttack.setFillColor(sf::Color::Black);
	my2ndAttack.setPosition(10, 2);
	myTextDead.setFont(myFont);
	myTextDead.setCharacterSize(60);
	myTextDead.setFillColor(sf::Color(0,15,137,155));
	myTextDead.setPosition(75, 300);
	myTextDead.setString("YOU DIED PRESS 'SPACE' TO PLAY AGAIN");
	myBoostText.setFont(myFont);
	myBoostText.setCharacterSize(36);
	myBoostText.setFillColor(sf::Color::Black);
	myBoostText.setPosition(500, 100);
	myHealthText.setFont(myFont);
	myHealthText.setCharacterSize(24);
	myHealthText.setPosition(1100, 2);
	myHealthText.setFillColor(sf::Color::Black);
	myWin = 0;
	myWinText.setFont(myFont);
	myWinText.setCharacterSize(60);
	myWinText.setFillColor(sf::Color(0, 15, 137, 255));
	myWinText.setPosition(450, 300);
	myWinText.setString("YOU WON!");
	myStory.setFont(myFont);
	myStory.setCharacterSize(60);
	myStory.setFillColor(sf::Color::Black);
	myStory.setPosition(100, 725);
	myTimeStory = 5.f;
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
	myTextTimer += someDelta;

	if (myBoxes[0].myVal != 2)
	{
		myTextE.setString("Press 'E' to pickup!");
	}
	else
	{
		myTextE.setString("Press 'E' to use!");
	}
	
	for (size_t i = 0; i < myTileMap.myWalls.size(); i++)
	{
		if (myPlayer.myRect.intersects(myTileMap.myWalls[i].getGlobalBounds()))
		{
			myPlayer.Damage(-999);
		}
	}

	if (myDoor.myNextLevel)
	{
		myCurLevel++;
		LoadLevel(myCurLevel);
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mySpecial)
	{
		//std::cout << "YEET" << std::endl;
		mySpecial = false;
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

	myTimerStory += someDelta;

	for (size_t i = 0; i < mySpecialBullets.size(); i++)
	{
		mySpecialBullets[i].Update(someDelta);
		myBroken = false;

		if (mySpecialBullets[i].myBullet.getPosition().x < 0 || mySpecialBullets[i].myBullet.getPosition().x > aWindow.getSize().x
			|| mySpecialBullets[i].myBullet.getPosition().y < 0 || mySpecialBullets[i].myBullet.getPosition().y > aWindow.getSize().y)
		{
			mySpecialBullets.erase(mySpecialBullets.begin() + i);
			break;
		}
		for (auto& enemy : myEnemies)
		{
			if (mySpecialBullets[i].myRect.intersects(enemy.myRect))
			{
				mySpecialBullets.erase(mySpecialBullets.begin() + i);
				enemy.myHealth -= 5;
				//NY
				myBroken = true;
				break;
			}
		}
		if (!myBroken)
		{
			for (auto& wall : myTileMap.myWalls)
			{
				if (mySpecialBullets[i].myRect.intersects(wall.getGlobalBounds()))
				{
					mySpecialBullets.erase(mySpecialBullets.begin() + i);
					break;
				}
			}
		}
	}
	myTextE.setPosition(myPlayer.myCenter.x - (myTextE.getLocalBounds().width / 2), myPlayer.myCenter.y - 75.f);

	for (size_t i = 0; i < myBoxes.size(); i++)
	{
		if (myBoxes[i].GetPickable() && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			myPlayer.myHealth += 3;
			if (myBoxes[i].myVal == 0)
			{
				mySpecial = true;
				myBoxes.erase(myBoxes.begin() + i);
			}
			else if (myBoxes[i].myVal == 1)
			{
				srand(time(NULL));
				switch (rand() % 2)
				{
					default:
						break;
					case 0:
						myTimerSpeed = .15f;
						myTextTimer = 0;
						myBoostText.setString("Attack speed increased");
						break;
					case 1:
						damage = 1.5f;
						myTextTimer = 0;
						myBoostText.setString("Damage increased");
						break;
				}
				myBoxes.erase(myBoxes.begin() + i);
			}
			else if (myBoxes[0].myVal == 2)
			{
				myDoorActive = false;
				for (size_t i = 0; i < 2; i++)
				{
					myTileMap.myWalls.erase(myTileMap.myWalls.end() - 1);
					break;
				}
				myTileMap.mySprites.resize(myTileMap.mySprites.size() + 1);
				myTileMap.mySprites.back().setTexture(myGroundTex);
				myTileMap.mySprites.back().setScale(2.f, 2.f);
				myTileMap.mySprites.back().setTextureRect(sf::IntRect(16, 128, 16, 16));
				myTileMap.mySprites.back().setPosition({ 32 * 17, 32 * 5 });
				myTileMap.mySprites.resize(myTileMap.mySprites.size() + 1);
				myTileMap.mySprites.back().setTexture(myGroundTex);
				myTileMap.mySprites.back().setScale(2.f, 2.f);
				myTileMap.mySprites.back().setTextureRect(sf::IntRect(16, 128, 16, 16));
				myTileMap.mySprites.back().setPosition({ 32 * 18, 32 * 5 });
				myTileMap.mySprites.resize(myTileMap.mySprites.size() + 1);
				myTileMap.mySprites.back().setTexture(myGroundTex);
				myTileMap.mySprites.back().setScale(2.f, 2.f);
				myTileMap.mySprites.back().setTextureRect(sf::IntRect(16, 128, 16, 16));
				myTileMap.mySprites.back().setPosition({ 32 * 19, 32 * 5 });
			}
		}
	}
	if (myPlayer.myHealth <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		LoadLevel(0);
	}
	else
	{
		myHealthText.setString("Health: " + std::to_string(myPlayer.myHealth));
	}

	for (size_t i = 0; i < myBullets.size(); i++)
	{
		myBullets[i].Update(someDelta);
		myBroken = false;

		if (myBullets[i].myBullet.getPosition().x < 0 || myBullets[i].myBullet.getPosition().x > aWindow.getSize().x
			|| myBullets[i].myBullet.getPosition().y < 0 || myBullets[i].myBullet.getPosition().y > aWindow.getSize().y)
		{
			myBullets.erase(myBullets.begin() + i);
			break;
		}
		for (auto& enemy : myEnemies)
		{
			if (myBullets[i].myRect.intersects(enemy.myRect))
			{
				enemy.myHealth -= damage;
				//NY
				myBullets.erase(myBullets.begin() + i);
				myBroken = true;
				break;
			}
		}
		if (!myBroken)
		{
			for (auto& wall : myTileMap.myWalls)
			{
				if (myBullets[i].myRect.intersects(wall.getGlobalBounds()))
				{
					myBullets.erase(myBullets.begin() + i);
					break;
				}
			}
		}
	}
	for (size_t i = 0; i < myEnemies.size(); i++)
	{
		myEnemies[i].Update(someDelta, aWindow);
		if (myEnemies[i].myHealth <= 0)
		{
			myEnemies.erase(myEnemies.begin() + i);
			if (myWin >= 1)
			{
				myWin++;
			}
			break;
		}
	}
	for (auto& box : myBoxes)
	{
		box.Update(someDelta, aWindow);
	}
	myPlayer.Update(someDelta, aWindow);
	myDoor.Update(someDelta, aWindow);
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

	if (mySpecial)
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
	if (myPlayer.myHealth <= 0)
	{
		aWindow.draw(myTextDead);
	}
	myDoor.Draw(aWindow);
	aWindow.draw(myHealthText);
	if (myTextTimer < myTextTime)
	{
		aWindow.draw(myBoostText);
	}
	if (myWin == 4)
	{
		aWindow.draw(myWinText);
	}
	if (myTimerStory < myTimeStory)
	{
		aWindow.draw(myStory);
	}
}

void App::LoadLevel(int aLvlNumber)
{
	myTextTimer = 0;
	myEnemies.clear();
	myTileMap.myWalls.clear();
	myTileMap.mySprites.clear();
	myPlayer.Init(myTexture, myFont);
	myDoor.Init(myPlayer);
	myBoxes.clear();
	App::myTimer = 0;
	myTimerStory = 0;
	if (aLvlNumber == 0)
	{
		myTileMap.Init(0);
		damage = 1;
		myTimerSpeed = 0.2f;
		myBoxes.emplace_back();
		myBoxes[0].Init(myPlayer, sf::Vector2f(100,100), 0);
		myEnemies.emplace_back(myPlayer, sf::Vector2f(375, 600), myTileMap.myWalls, false);
		myEnemies.emplace_back(myPlayer, sf::Vector2f(600, 50), myTileMap.myWalls, false);
		myEnemies.emplace_back(myPlayer, sf::Vector2f(1000, 400), myTileMap.myWalls, false);
		App::mySpecial = false;
		myCurLevel = 0;
		myWin = 0;
		myStory.setString("YOU ARE CHOSEN TO KILL ALL!");
	}
	else if (aLvlNumber == 1)
	{
		myTileMap.Init(1);
		myCurLevel = 1;
		myBoxes.emplace_back();
		myBoxes[0].Init(myPlayer, sf::Vector2f(800, 195), 1);
		myStory.setString("GOOD JOB NOW COMPLETE THE MACE!");
	}
	else if (aLvlNumber == 2)
	{
		myTileMap.Init(2);
		myCurLevel = 2;
		myBoxes.emplace_back();
		myBoxes[0].Init(myPlayer, sf::Vector2f(-100, -100), 0);
		myEnemies.emplace_back(myPlayer, sf::Vector2f(75, 650), myTileMap.myWalls, false);
		myEnemies.emplace_back(myPlayer, sf::Vector2f(430, 475), myTileMap.myWalls, false);
		myEnemies.emplace_back(myPlayer, sf::Vector2f(215, 345), myTileMap.myWalls, false);
		myEnemies.emplace_back(myPlayer, sf::Vector2f(650, 70), myTileMap.myWalls, false);
		myEnemies.emplace_back(myPlayer, sf::Vector2f(800, 335), myTileMap.myWalls, false);
		myStory.setString("OH NO! YOU MUST KILL THEM!");
	}
	else if (aLvlNumber == 3)
	{
		myTileMap.Init(3);
		myCurLevel = 3;
		myBoxes.emplace_back();
		myBoxes[0].Init(myPlayer, sf::Vector2f(200, 75), 2);
		myDoorActive = true;
		myStory.setString("WELL DONE. HOW IS THIS POSSIBLE?");
	}
	else if (aLvlNumber == 4)
	{
		myDoor.myShape.setPosition(-100, -100);
		myTileMap.Init(4);
		myCurLevel = 4;
		myBoxes.emplace_back();
		myBoxes[0].Init(myPlayer, sf::Vector2f(375,400), 0);
		myEnemies.emplace_back(myPlayer, sf::Vector2f(510, 200), myTileMap.myWalls, false);
		myEnemies.emplace_back(myPlayer, sf::Vector2f(510, 550), myTileMap.myWalls, false);
		myEnemies.emplace_back(myPlayer, sf::Vector2f(950, 320), myTileMap.myWalls, true);
		myWin++;
		myStory.setString("DANGER!!!!! KILL THE BOSS!!!");
	}
}