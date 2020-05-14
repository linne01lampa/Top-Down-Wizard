#ifndef BOX_HEADER
#define BOX_HEADER

#include <SFML/Graphics.hpp>
#include "Player.h"

class Box
{
public:
	Box();
	~Box();

	void Init(Player &aPlayer);

	void Update(const float& someDelta, sf::RenderWindow& aWindow);
	void Draw(sf::RenderWindow& aWindow);

	bool GetPickable();

	sf::Vector2f myCenter;
	sf::RectangleShape myShape;
	sf::FloatRect myRect;

	bool pickable;	
private:
	Player* myPlayer;
};

#endif
