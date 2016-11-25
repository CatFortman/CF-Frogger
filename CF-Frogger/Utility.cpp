#include "Utility.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <cassert>

namespace GEX
{
	void centerOrigin(sf::Sprite& sprite)
	{
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	void centerOrigin(sf::Text& text)
	{
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	void centerOrigin(Animation& animation)
	{
		sf::FloatRect bounds = animation.getLocalBounds();
		animation.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	float length(sf::Vector2f vector)
	{
		return sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	sf::Vector2f unitVector(sf::Vector2f vector)
	{
		assert(vector != sf::Vector2f(0.f, 0.f));
		return vector / length(vector);
	}
}