#pragma once
#include "SFML/graphics.hpp"
#include "PlayerControl.h"
#include "StateStack.h"
#include "CommandQueue.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

namespace GEX
{
	class Application
	{
	public:
		Application();
		void                    run();

	private:
		void                    processInput();
		void                    update(sf::Time dt);
		void                    render();

		void                    updateStatistics(sf::Time dt);
		void                    registerStates();

	private:
		static const sf::Time   TimePerFrame;

		sf::RenderWindow        _window;
		PlayerControl           _player;
		MusicPlayer				_music;
		SoundPlayer				_sounds;

		StateStack              _stateStack;

		sf::Text                _statsText;
	};
}
