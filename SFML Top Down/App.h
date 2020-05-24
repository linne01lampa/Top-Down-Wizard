#ifndef APP_HEADER
#define APP_HEADER

#include <vector>
#include <SFML/Graphics.hpp>
#include "Box.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "TileMap.h"
#include "Door.h"

class App
{
public:
	App(sf::RenderWindow& aWindow);
	~App();

	void Update(const float& someDelta, sf::RenderWindow& aWindow);
	void Draw(sf::RenderWindow& aWindow);
private:
	sf::Vector2f myMousePos;
	Player myPlayer;
	Door myDoor;
	TileMap myTileMap;
	std::vector<Enemy> myEnemies;
	std::vector<Box> myBoxes;
	sf::Texture myTexture;
	std::vector<Bullet> myBullets;
	sf::Vector2f myAim;
	sf::Vector2f myNorm;
	float myTimer;
	float myTimerSpeed = .2f;
	bool mySpecial;
	std::vector<Bullet> mySpecialBullets;
	sf::Font myFont;
	sf::Text myTextE;
	sf::Text my2ndAttack;
	sf::Text myTextDead;
	void Type(const char * p);
	void LoadLevel(int aLvlNumber);
	int myCurLevel;
	bool myBroken;
	float damage;
	sf::Text myBoostText;
	float myTextTimer = 4.f;
	float myTextTime = 3.f;
	bool myDoorActive;
	sf::Texture myGroundTex;
	sf::Text myHealthText;
	int myWin;
	sf::Text myWinText;
	sf::Text myStory;
	float myTimerStory;
	float myTimeStory;
};

#endif
