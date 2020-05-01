#ifndef APP_HEADER
#define APP_HEADER

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "TileMap.h"
#include "Enemy.h"
#include <vector>

class App
{
public:
	App();
	~App();

	void Update(const float& someDelta, sf::RenderWindow& aWindow);
	void Draw(sf::RenderWindow& aWindow);
private:
	sf::Vector2f myMousePos;
	Player myPlayer;
	TileMap myTileMap;
	Enemy myEnemy;
	sf::Texture myTexture;
	std::vector<Bullet> myBullets;
	sf::Vector2f myAim;
	sf::Vector2f myNorm;
	float myTimer;
	float myTimerSpeed = .2f;
};

#endif