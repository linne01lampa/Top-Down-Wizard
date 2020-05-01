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
	sf::Vector2f myCenter;
private:
	sf::Sprite mySprite;
	float mySpeed;
};
#endif