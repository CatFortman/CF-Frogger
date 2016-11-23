#pragma once
#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "CommandQueue.h"

namespace GEX
{
	class GexState : public State
	{
	public:
		GexState(StateStack& stack, Context context);

		virtual void        draw();
		virtual bool        update(sf::Time dt);
		virtual bool        handleEvent(const sf::Event& event);


	private:
		sf::Sprite          _backgroundSprite;
		sf::Text            _gamePausedText;
		sf::Text            _gexText;
		sf::Text            _backspaceText;
		sf::Text            _gText;
	};
}