#include "Bullet.h"

Bullet::Bullet(sf::Vector2f aDir, float someSpeed, sf::Vector2f start)
{
	myDir = aDir;
	myBullet.setRadius(8.f);
	myBullet.setFillColor(sf::Color::Black);
	mySpeed = someSpeed;
	myBullet.setPosition(start);
}
Bullet::~Bullet()
{

}

//void Bullet::Init(const sf::Vector2f aDir, float &someSpeed)
//{
//	myDir = aDir;
//	myBullet.setRadius(.5f);
//	myBullet.setFillColor(sf::Color::Black);
//	mySpeed = someSpeed;
//}

void Bullet::Update(const float& someDelta)
{
	myBullet.move(myDir * someDelta * mySpeed);
	myTrail.SetPosition(myBullet.getPosition() + 0.5f * sf::Vector2f(myBullet.getRadius(), myBullet.getRadius()));
	myTrail.Update(someDelta);
}

void Bullet::Draw(sf::RenderWindow& aWindow)
{
	aWindow.draw(myTrail);
	aWindow.draw(myBullet);
}



