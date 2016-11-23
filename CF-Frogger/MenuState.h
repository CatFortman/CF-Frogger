#pragma once

#include "State.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "Component.h"
#include "Container.h"
#include "Button.h"

namespace GEX
{
	class Component; // forward declaration
	class Container;

	class MenuState : public State
	{
	public:
		MenuState(StateStack& stack, Context context);

		void draw();
		bool update(sf::Time);
		bool handleEvent(const sf::Event& event);

	private:
		sf::Sprite		_mBackgroundSprite;
		GUI::Container	_mGUIContainer;
	};
}

