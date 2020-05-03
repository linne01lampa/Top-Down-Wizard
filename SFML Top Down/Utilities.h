#pragma once

#include "SFML/System/Vector2.hpp"

namespace Math
{
	void Normalize(sf::Vector2f& aVector);
	float Length2(const sf::Vector2f&);
	float Length(const sf::Vector2f&);
}

namespace Random
{
	float GetValue(float aMin, float aMax);
}