#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	//Player();
	~Player();

	void Init(const sf::Texture& aTexture, sf::Font aFont);

	void Update(const float& someDelta, sf::RenderWindow& aWindow);
	void Draw(sf::RenderWindow& aWindow);
	sf::Vector2f myCenter;
	sf::FloatRect myRect;
	void Damage(int someDamage);
	int myHealth;
private:
	sf::Sprite mySprite;
	float mySpeed;
	sf::Vector2f myLastPos;
	int myDir;
};
#endif