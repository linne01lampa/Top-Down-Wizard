#include <iostream>
#include "App.h"

#define _USE_MATH_DEFINES

#include "SFML/Window/Window.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Math.h"

//using namespace std;
//using namespace sf;

//void Update(CircleShape& djuret, RenderWindow& window, CircleShape& bul, float &xDir, float &yDir);
//void Draw(RenderWindow &window, CircleShape &djuret, CircleShape &bul);

int main()
{
	//sf::VideoMode vm;
	//vm.height = 200;
	//vm.width = 200;


	sf::RenderWindow myWindow(sf::VideoMode(1200, 800), "djur", sf::Style::Default);
	//myWindow.setFramerateLimit(60);
	//sf::View myView(sf::Vector2f(myWindow.getSize().x / 2, myWindow.getSize().y / 2 - 30), sf::Vector2f(1000.f,1000.f));

	App tempApp(myWindow);
	
	sf::Clock tempClock;
	sf::Time tempDelta;

	//sf::CircleShape djuret(50.f);
	//djuret.setPosition(sf::Vector2f(300.f, 200.f));
	//djuret.setPointCount(20);
	//djuret.setFillColor(sf::Color(199,21,133,255));
	//djuret.setOutlineColor(sf::Color::Magenta);
	//djuret.setOutlineThickness(4.f);
	//djuret.setOrigin(djuret.getRadius(), djuret.getRadius());
	//RectangleShape rect(Vector2f(15.f, 20.f));

	//sf::CircleShape bul;
	//bul.setRadius(15.f);
	//bul.setOutlineColor(sf::Color::Black);
	//bul.setPosition(100.f, 100.f);
	////bul.setPosition(djuret.getPosition());
	//bul.setOrigin(bul.getRadius(), bul.getRadius());
	//float xDir, yDir = 0;

	while (myWindow.isOpen())
	{
		tempDelta = tempClock.restart();

		sf::Event event;
		while (myWindow.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				myWindow.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				myWindow.close();
			}
		}

		tempApp.Update(tempDelta.asSeconds(),myWindow);

		/*if (tempApp.Update(tempDelta.asSeconds()) == false)
		{
			return 0;
		}*/

		myWindow.clear(sf::Color(207, 185, 151, 255));
		//myWindow.setView(myView);
		tempApp.Draw(myWindow);
		myWindow.display();

		//Update
		//Update(djuret, w, bul, xDir, yDir);

		////Draw
		//Draw(w, djuret, bul);
	}

	//std::cout << "HEJ" << std::endl;
	return 0;
}



//void Update(sf::CircleShape &djuret, sf::RenderWindow &window, sf::CircleShape &bul, float& xDir, float& yDir)
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && djuret.getPosition().y - djuret.getRadius() > 0)
//	{
//		djuret.move(sf::Vector2f(0.f, -1.5f));
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && djuret.getPosition().y + djuret.getRadius() < window.getSize().y)
//	{
//		djuret.move(sf::Vector2f(0.f, 1.5f));
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && djuret.getPosition().x - djuret.getRadius() > 0)
//	{
//		djuret.move(sf::Vector2f(-1.5f, 0.f));
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && djuret.getPosition().x + djuret.getRadius() < window.getSize().x)
//	{
//		djuret.move(sf::Vector2f(1.5f, 0.f));
//	}
//
//	float rad = (M_PI / 180) * djuret.getRotation();
//
//	//bul.move(Vector2f(cos(rad) * 10.f, sin(rad) * 10.f));
//
//	bul.move(xDir, yDir);
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//	{
//		bul.setPosition(djuret.getPosition());
//		xDir = cos(rad);
//		yDir = sin(rad);
//	}
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
//	{
//		djuret.rotate(1.f);
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
//	{
//		djuret.rotate(-1.f);
//	}
////}
//
//
//void Draw(sf::RenderWindow &window, sf::CircleShape &djuret, sf::CircleShape &bul)
//{
//	window.clear(sf::Color::Color(255,105,180,255));
//	window.draw(djuret);
//	window.draw(bul);
//	window.display();
//}