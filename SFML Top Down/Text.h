#ifndef TEXT_HEADER
#define TEXT_HEADER
#include "SFML/Graphics.hpp"
#include <string>
class Text
{
public:
	Text();
	~Text();

	void Init(sf::Font);
	
	void Update(const float& someDelta, sf::RenderWindow& aWindow);
	void Draw(sf::RenderWindow& aWindow);
private:
	int myCharacters;
	sf::Clock myTimer;
	std::string myText;
	sf::Text myWrittenText;
	sf::Font myFont;
};
#endif