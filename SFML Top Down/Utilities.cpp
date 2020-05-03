#include "Utilities.h"
#include <math.h>
#include <utility>
#include <limits>

void Math::Normalize(sf::Vector2f& aVector)
{
	float length = sqrt(Length2(aVector));
	aVector.x /= length;
	aVector.y /= length;
}

float Math::Length2(const sf::Vector2f& aVector)
{
	return aVector.x * aVector.x + aVector.y * aVector.y;
}

float Math::Length(const sf::Vector2f& aVector)
{
	return sqrt(Length2(aVector));
}

float Random::GetValue(float aMin, float aMax)
{
	return aMin + (static_cast<float>(rand()) / RAND_MAX) * (aMax - aMin);
}
