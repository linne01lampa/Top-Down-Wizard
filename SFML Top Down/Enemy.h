#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init(Player &aPlayer);

	void Update(const float& someDelta, sf::RenderWindow& aWindow);
	void Draw(sf::RenderWindow &aWindow);
	sf::Vector2f myCenter;
	void Fire();
	sf::CircleShape myShape;
	sf::FloatRect myRect;


private:
	float mySpeed;
	Player* myPlayer;
	bool reloaded;
	std::vector<Bullet> myBullets;
	float myTimer;
	float myTimerSpeed = .2f;
};

#endif