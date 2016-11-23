#pragma once
#include "SFML\Graphics.hpp"

namespace GEX
{
	struct Particle
	{
		enum class  Type { propellant, smoke };

		sf::Vector2f	position;
		sf::Color		color;
		sf::Time		lifetime;
	};
}
