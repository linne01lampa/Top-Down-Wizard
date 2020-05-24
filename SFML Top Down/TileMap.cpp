#include "TileMap.h"
#include <SFML/System.hpp>
#include <random>


TileMap::TileMap()
{
	
}

TileMap::~TileMap()
{

}

void TileMap::Init(int level)
{
	myGroundTex.loadFromFile("tileset.png");
	myLavaTex.loadFromFile("tileset.png");
	mySprites.reserve(30 * 40);
	gBounds = myGroundTex.getSize();

	for (unsigned x = 0; x < 40; x++)
	{
		for (unsigned y = 0; y < 30; y++)
		{
			if (level == 0)
			{
				if (map1[y][x] == 0)
				{
					switch (rand() % 2)
					{
						default:
							break;
						case 0:
							myWalls.resize(myWalls.size() + 1);
							//myWalls.back().setTexture(myGroundTex);
							myWalls.back().setTexture(myLavaTex);
							myWalls.back().setScale(2.f, 2.f);
							myWalls.back().setTextureRect(sf::IntRect(32, 144, 16, 16));
							myWalls.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
						case 1:
							myWalls.resize(myWalls.size() + 1);
							//myWalls.back().setTexture(myGroundTex);
							myWalls.back().setTexture(myLavaTex);
							myWalls.back().setScale(2.f, 2.f);
							myWalls.back().setTextureRect(sf::IntRect(48, 144, 16, 16));
							myWalls.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
					}

					//break;
				}
				else if (map1[y][x] == 1)
				{
					switch (rand() % 2)
					{
						default:
							break;
						case 0:
							mySprites.resize(mySprites.size() + 1);
							mySprites.back().setTexture(myGroundTex);
							mySprites.back().setScale(2.f, 2.f);
							mySprites.back().setTextureRect(sf::IntRect(0, 128, 16, 16));
							mySprites.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
						case 1:
							mySprites.resize(mySprites.size() + 1);
							mySprites.back().setTexture(myGroundTex);
							mySprites.back().setScale(2.f, 2.f);
							mySprites.back().setTextureRect(sf::IntRect(16, 128, 16, 16));
							mySprites.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
					}

					//mySprites[0].setPosition(0.f, 0.f);
					//mySprites[1].setPosition(gBounds.x * float(x), gBounds.y * float(y));
				}
			}
			else if (level == 1)
			{
				if (map2[y][x] == 0)
				{
					switch (rand() % 2)
					{
						default:
							break;
						case 0:
							myWalls.resize(myWalls.size() + 1);
							//myWalls.back().setTexture(myGroundTex);
							myWalls.back().setTexture(myLavaTex);
							myWalls.back().setScale(2.f, 2.f);
							myWalls.back().setTextureRect(sf::IntRect(32, 144, 16, 16));
							myWalls.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
						case 1:
							myWalls.resize(myWalls.size() + 1);
							//myWalls.back().setTexture(myGroundTex);
							myWalls.back().setTexture(myLavaTex);
							myWalls.back().setScale(2.f, 2.f);
							myWalls.back().setTextureRect(sf::IntRect(48, 144, 16, 16));
							myWalls.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
					}

					//break;
				}
				else if (map2[y][x] == 1)
				{
					switch (rand() % 2)
					{
						default:
							break;
						case 0:
							mySprites.resize(mySprites.size() + 1);
							mySprites.back().setTexture(myGroundTex);
							mySprites.back().setScale(2.f, 2.f);
							mySprites.back().setTextureRect(sf::IntRect(0, 128, 16, 16));
							mySprites.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
						case 1:
							mySprites.resize(mySprites.size() + 1);
							mySprites.back().setTexture(myGroundTex);
							mySprites.back().setScale(2.f, 2.f);
							mySprites.back().setTextureRect(sf::IntRect(16, 128, 16, 16));
							mySprites.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
					}

					//mySprites[0].setPosition(0.f, 0.f);
					//mySprites[1].setPosition(gBounds.x * float(x), gBounds.y * float(y));
				}
			}
			else if (level == 2)
			{
				if (map3[y][x] == 0)
				{
					switch (rand() % 2)
					{
						default:
							break;
						case 0:
							myWalls.resize(myWalls.size() + 1);
							//myWalls.back().setTexture(myGroundTex);
							myWalls.back().setTexture(myLavaTex);
							myWalls.back().setScale(2.f, 2.f);
							myWalls.back().setTextureRect(sf::IntRect(32, 144, 16, 16));
							myWalls.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
						case 1:
							myWalls.resize(myWalls.size() + 1);
							//myWalls.back().setTexture(myGroundTex);
							myWalls.back().setTexture(myLavaTex);
							myWalls.back().setScale(2.f, 2.f);
							myWalls.back().setTextureRect(sf::IntRect(48, 144, 16, 16));
							myWalls.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
					}

					//break;
				}
				else if (map3[y][x] == 1)
				{
					switch (rand() % 2)
					{
						default:
							break;
						case 0:
							mySprites.resize(mySprites.size() + 1);
							mySprites.back().setTexture(myGroundTex);
							mySprites.back().setScale(2.f, 2.f);
							mySprites.back().setTextureRect(sf::IntRect(0, 128, 16, 16));
							mySprites.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
						case 1:
							mySprites.resize(mySprites.size() + 1);
							mySprites.back().setTexture(myGroundTex);
							mySprites.back().setScale(2.f, 2.f);
							mySprites.back().setTextureRect(sf::IntRect(16, 128, 16, 16));
							mySprites.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
					}

					//mySprites[0].setPosition(0.f, 0.f);
					//mySprites[1].setPosition(gBounds.x * float(x), gBounds.y * float(y));
				}
			}
			else if (level == 3)
			{
				if (map4[y][x] == 0)
				{
					switch (rand() % 2)
					{
						default:
							break;
						case 0:
							myWalls.resize(myWalls.size() + 1);
							//myWalls.back().setTexture(myGroundTex);
							myWalls.back().setTexture(myLavaTex);
							myWalls.back().setScale(2.f, 2.f);
							myWalls.back().setTextureRect(sf::IntRect(32, 144, 16, 16));
							myWalls.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
						case 1:
							myWalls.resize(myWalls.size() + 1);
							//myWalls.back().setTexture(myGroundTex);
							myWalls.back().setTexture(myLavaTex);
							myWalls.back().setScale(2.f, 2.f);
							myWalls.back().setTextureRect(sf::IntRect(48, 144, 16, 16));
							myWalls.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
					}

					//break;
				}
				else if (map4[y][x] == 1)
				{
					switch (rand() % 2)
					{
						default:
							break;
						case 0:
							mySprites.resize(mySprites.size() + 1);
							mySprites.back().setTexture(myGroundTex);
							mySprites.back().setScale(2.f, 2.f);
							mySprites.back().setTextureRect(sf::IntRect(0, 128, 16, 16));
							mySprites.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
						case 1:
							mySprites.resize(mySprites.size() + 1);
							mySprites.back().setTexture(myGroundTex);
							mySprites.back().setScale(2.f, 2.f);
							mySprites.back().setTextureRect(sf::IntRect(16, 128, 16, 16));
							mySprites.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
					}

					//mySprites[0].setPosition(0.f, 0.f);
					//mySprites[1].setPosition(gBounds.x * float(x), gBounds.y * float(y));
				}
			}
			else if (level == 4)
			{
				if (map5[y][x] == 0)
				{
					switch (rand() % 2)
					{
						default:
							break;
						case 0:
							myWalls.resize(myWalls.size() + 1);
							//myWalls.back().setTexture(myGroundTex);
							myWalls.back().setTexture(myLavaTex);
							myWalls.back().setScale(2.f, 2.f);
							myWalls.back().setTextureRect(sf::IntRect(32, 144, 16, 16));
							myWalls.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
						case 1:
							myWalls.resize(myWalls.size() + 1);
							//myWalls.back().setTexture(myGroundTex);
							myWalls.back().setTexture(myLavaTex);
							myWalls.back().setScale(2.f, 2.f);
							myWalls.back().setTextureRect(sf::IntRect(48, 144, 16, 16));
							myWalls.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
					}

					//break;
				}
				else if (map5[y][x] == 1)
				{
					switch (rand() % 2)
					{
						default:
							break;
						case 0:
							mySprites.resize(mySprites.size() + 1);
							mySprites.back().setTexture(myGroundTex);
							mySprites.back().setScale(2.f, 2.f);
							mySprites.back().setTextureRect(sf::IntRect(0, 128, 16, 16));
							mySprites.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
						case 1:
							mySprites.resize(mySprites.size() + 1);
							mySprites.back().setTexture(myGroundTex);
							mySprites.back().setScale(2.f, 2.f);
							mySprites.back().setTextureRect(sf::IntRect(16, 128, 16, 16));
							mySprites.back().setPosition({ 32 * float(x), 32 * float(y) });
							break;
					}

					//mySprites[0].setPosition(0.f, 0.f);
					//mySprites[1].setPosition(gBounds.x * float(x), gBounds.y * float(y));
				}
			}
			/*else if (map1[y][x] == 2)
			{
				mySprites.resize(mySprites.size() + 1);
				mySprites.back().setTexture(myGroundTex);
				mySprites.back().setScale(2.f, 2.f);
				mySprites.back().setTextureRect(sf::IntRect(16, 128, 16, 16));
				mySprites.back().setPosition({ 32 * float(x), 32 * float(y) });
			}*/
		}
	}
	if (level == 3)
	{
		for (unsigned x = 0; x < 40; x++)
		{
			for (unsigned y = 0; y < 30; y++)
			{
				if (map4[y][x] == 2)
				{
					myWalls.resize(myWalls.size() + 1);
					//myWalls.back().setTexture(myGroundTex);
					myWalls.back().setTexture(myLavaTex);
					myWalls.back().setScale(2.f, 2.f);
					myWalls.back().setTextureRect(sf::IntRect(32, 144, 16, 16));
					myWalls.back().setPosition({ 32 * float(x), 32 * float(y) });
				}
			}
		}
	}
}

void TileMap::Draw(sf::RenderWindow& aWindow)
{
	for (sf::Sprite sprite : mySprites)
	{
		aWindow.draw(sprite);
	}
	for (sf::Sprite sprite : myWalls)
	{
		aWindow.draw(sprite);
	}
}