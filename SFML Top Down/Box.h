#ifndef BOX_HEADER
#define BOX_HEADER

#include <SFML/Graphics.hpp>
#include "Player.h"

class Box
{
public:
	Box();
	~Box();

	void Init(Player &aPlayer, sf::Vector2f aPosition, int aVal);

	void Update(const float& someDelta, sf::RenderWindow& aWindow);
	void Draw(sf::RenderWindow& aWindow);

	bool GetPickable();

	sf::Vector2f myCenter;
	sf::RectangleShape myShape;
	sf::FloatRect myRect;
	int myVal;

	bool pickable;	
private:
	Player* myPlayer;
};

#endif
