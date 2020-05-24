#ifndef DOOR_HEADER
#define DOOR_HEADER

#include <SFML/Graphics.hpp>
#include "Player.h"

class Door
{
public:
	Door();
	~Door();

	void Init(Player &aPlayer);

	void Update(const float& someDelta, sf::RenderWindow& aWindow);
	void Draw(sf::RenderWindow& aWindow);

	bool myNextLevel;
	
	sf::Vector2f myCenter;
	sf::RectangleShape myShape;
	sf::FloatRect myRect;
private:
	Player* myPlayer;
};
#endif