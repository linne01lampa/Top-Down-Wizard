#ifndef BULLET_HEADER
#define BULLET_HEADER

#include <SFML/Graphics.hpp>

#include "Trail.h"

class Bullet
{
public:
	Bullet(sf::Vector2f aDir, float someSpeed, sf::Vector2f start);
	~Bullet();

	//void Init(sf::Vector2f aDir);

	void Update(const float& someDelta);
	void Draw(sf::RenderWindow& aWindow);
	sf::CircleShape myBullet;
	ss::CTrail myTrail;
private:
	sf::Vector2f myDir;
	float mySpeed;

};
#endif