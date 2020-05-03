#ifndef BULLET_HEADER
#define BULLET_HEADER

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(sf::Vector2f aDir, float someSpeed, sf::Vector2f start);
	~Bullet();

	//void Init(sf::Vector2f aDir);

	void Update(const float& someDelta);
	void Draw(sf::RenderWindow& aWindow);
	sf::CircleShape myBullet;
	sf::FloatRect myRect;
private:
	sf::Vector2f myDir;
	float mySpeed;
};
#endif