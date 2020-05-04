#ifndef APP_HEADER
#define APP_HEADER

#include <vector>
#include <SFML/Graphics.hpp>
#include "Box.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "TileMap.h"

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
	std::vector<Enemy> myEnemies;
	Box myBox;
	sf::Texture myTexture;
	std::vector<Bullet> myBullets;
	sf::Vector2f myAim;
	sf::Vector2f myNorm;
	float myTimer;
	float myTimerSpeed = .2f;
	bool special;
	std::vector<Bullet> mySpecialBullet;
	sf::Font myFont;
	sf::Text myTextE;
};

#endif
