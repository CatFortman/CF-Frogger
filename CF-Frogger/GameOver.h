#pragma once

#include "State.h"
#include "CommandQueue.h"
#include "PlayerControl.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace GEX
{
	class GameOverState : public State
	{
	public:
		GameOverState(StateStack& stack, Context context);

		virtual void        draw();
		virtual bool        update(sf::Time dt);
		virtual bool        handleEvent(const sf::Event& event);


	private:
		sf::Text            _gameOverText;
		sf::Time			_elapsedTime;
	};
}