#pragma once

#include "State.h"
#include "CommandQueue.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace GEX
{
	class PauseState : public State
	{
	public:
		PauseState(StateStack& stack, Context context);

		virtual void        draw();
		virtual bool        update(sf::Time dt);
		virtual bool        handleEvent(const sf::Event& event);


	private:
		sf::Sprite          _backgroundSprite;
		sf::Text            _pausedText;
		sf::Text            _instructionText;
	};
}