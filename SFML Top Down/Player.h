#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();

	void Init(const sf::Texture& aTexture);

	void Update(const float& someDelta, sf::RenderWindow& aWindow);
	void Draw(sf::RenderWindow& aWindow);
	void MoveToLastPos();
	sf::Vector2f myCenter;
	sf::FloatRect myRect;
private:
	sf::Sprite mySprite;
	float mySpeed;
	sf::Vector2f myLastPos;
	int dir;
};
#endif