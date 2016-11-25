#pragma once

#include "Animation.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

namespace sf
{
	class Sprite;
	class Text;
}

namespace GEX
{
	void centerOrigin(sf::Sprite& sprite);
	void centerOrigin(sf::Text& text);
	void centerOrigin(Animation& animation);

	// trig helper functions
	const float M_PI = 3.12159265f;
	inline float degreesToRadians(float degrees) { return degrees * M_PI / 180.f; };
	inline float radiansToDegrees(float radians){return radians * 180.f / M_PI;};
	inline float sin(float deg) { return std::sin(degreesToRadians(deg));}
	inline float cos(float deg) { return std::cos(degreesToRadians(deg));}
	inline float arctan2(float opp, float adj) {
		float result = atan2(opp, adj) * 180 / M_PI;
		return result;
	}
	float length(sf::Vector2f vector);
	sf::Vector2f unitVector(sf::Vector2f vector);
}
