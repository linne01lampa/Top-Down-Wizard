#include "TileMap.h"
#include <SFML/System.hpp>
#include <random>


TileMap::TileMap()
{
	
}

TileMap::~TileMap()
{

}

void TileMap::Init()
{
	groundTex.loadFromFile("tileset.png");
	sprites.reserve(30 * 40);
	gBounds = groundTex.getSize();

	for (unsigned x = 0; x < 40; x++)
	{
		for (unsigned y = 0; y < 30; y++)
		{
			if (map[y][x] == 0)
			{
			myWalls.resize(myWalls.size() + 1);
			//myWalls.back().setTexture(groundTex);
			myWalls.back().setScale(2.f, 2.f);
			myWalls.back().setTextureRect(sf::IntRect(16, 128, 16, 16));
			myWalls.back().setPosition({ 32 * float(x), 32 * float(y) });
			//break;
			}
			if (map[y][x] == 1)
			{
				switch (rand() % 2)
				{
					default:
						break;
					case 0:
						sprites.resize(sprites.size() + 1);
						sprites.back().setTexture(groundTex);
						sprites.back().setScale(2.f, 2.f);
						sprites.back().setTextureRect(sf::IntRect(0, 128, 16, 16));
						sprites.back().setPosition({ 32 * float(x), 32 * float(y) });
						break;
					case 1:
						sprites.resize(sprites.size() + 1);
						sprites.back().setTexture(groundTex);
						sprites.back().setScale(2.f, 2.f);
						sprites.back().setTextureRect(sf::IntRect(16, 128, 16, 16));
						sprites.back().setPosition({ 32 * float(x), 32 * float(y) });
						break;
				}
				
				//sprites[0].setPosition(0.f, 0.f);
				//sprites[1].setPosition(gBounds.x * float(x), gBounds.y * float(y));
			}
			/*else if (map[y][x] == 2)
			{
				sprites.resize(sprites.size() + 1);
				sprites.back().setTexture(groundTex);
				sprites.back().setScale(2.f, 2.f);
				sprites.back().setTextureRect(sf::IntRect(16, 128, 16, 16));
				sprites.back().setPosition({ 32 * float(x), 32 * float(y) });
			}*/
		}
	}
}

void TileMap::Draw(sf::RenderWindow& aWindow)
{
	for (sf::Sprite sprite : sprites)
	{
		aWindow.draw(sprite);
	}
	for (sf::Sprite sprite : myWalls)
	{
		aWindow.draw(sprite);
	}
}
