#pragma once

#include "State.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"


namespace GEX
{
	class TitleState : public State
	{
	public:
		TitleState(StateStack& stack, Context context);

		virtual void        draw();
		virtual bool        update(sf::Time dt);
		virtual bool        handleEvent(const sf::Event& event);

	private:
		sf::Sprite          _backgroundSprite;
		sf::Text            _text;

		bool                _showText;
		sf::Time            _textEffectTime;
	};
}
