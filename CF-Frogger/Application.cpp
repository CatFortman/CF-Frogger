#include "Application.h"
#include "TextureHolder.h"
#include "Utility.h"
#include "State.h"
#include "StateIdentifiers.h"
#include "TitleState.h"
#include "GameState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GexState.h"
#include "FontHolder.h"
#include "SFML\Audio.hpp"

namespace GEX
{
	const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

	Application::Application() :
		_window(sf::VideoMode(480, 600), "States", sf::Style::Close),
		_player(),
		_stateStack(State::Context(_window, _player, _music, _sounds)),
		_statsText()
	{
		_window.setKeyRepeatEnabled(false);

		FontHolder::getInstance().load(FontID::Main, "Media/Player.ttf");
		TextureHolder::getInstance().load(TextureID::TitleScreen, "Media/Textures/FroggerTitle.png");
		TextureHolder::getInstance().load(TextureID::MenuScreen, "Media/Textures/Frogger.png");
		TextureHolder::getInstance().load(TextureID::Face, "Media/Textures/face.png");
		TextureHolder::getInstance().load(TextureID::RedQuit, "Media/Textures/quitRed.png");
		TextureHolder::getInstance().load(TextureID::GreenQuit, "Media/Textures/quitGreen.png");
		TextureHolder::getInstance().load(TextureID::RedPlay, "Media/Textures/startRed.png");
		TextureHolder::getInstance().load(TextureID::GreenPlay, "Media/Textures/startGreen.png");
		TextureHolder::getInstance().load(TextureID::Particle, "Media/Textures/particle.png");
		TextureHolder::getInstance().load(TextureID::Explosion, "Media/Textures/Explosion.png");
		TextureHolder::getInstance().load(TextureID::Background, "Media/Textures/background.jpg");
		TextureHolder::getInstance().load(TextureID::Frog, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::FrogJump, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::FrogLives, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::Car, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::RaceCarL, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::RaceCarR, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::Tractor, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::Truck, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::tree1, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::tree2, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::turtles1, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::turtles2, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::turtles3, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::turtles4, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::threeTurtles1, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::threeTurtles2, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::threeTurtles3, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::threeTurtles4, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::die1, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::die2, "Media/Textures/FroggerAtlas.png");
		TextureHolder::getInstance().load(TextureID::die3, "Media/Textures/FroggerAtlas.png");

		_statsText.setFont(FontHolder::getInstance().get(FontID::Main));
		_statsText.setPosition(5.f, 5.f);
		_statsText.setCharacterSize(10u);

		registerStates();
		_stateStack.pushState(StateID::Title);	
	}

	void Application::run()
	{
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;

		while (_window.isOpen())
		{
			sf::Time dt = clock.restart();
			timeSinceLastUpdate += dt;
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;

				processInput();
				update(TimePerFrame);

				// Check inside this loop, because stack might be empty before update() call
				if (_stateStack.isEmpty())
					_window.close();
			}

			updateStatistics(dt);
			render();
		}
	}

	void Application::processInput()
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			_stateStack.handleEvent(event);

			if (event.type == sf::Event::Closed)
				_window.close();
		}
	}

	void Application::update(sf::Time dt)
	{
		_stateStack.update(dt);
	}

	void Application::render()
	{
		_window.clear();
		_stateStack.draw();

		_window.setView(_window.getDefaultView());
		_window.draw(_statsText);

		_window.display();
	}

	void Application::updateStatistics(sf::Time dt)
	{
		//_statisticsUpdateTime += dt;
		static sf::Time updateTime = sf::Time::Zero;
		static int  numFrames = 0;

		updateTime += dt;
		numFrames += 1;
		if (updateTime >= sf::seconds(1.0f))
		{
			_statsText.setString(
				"Frames / Second = " + std::to_string(numFrames) + "\n" +
				"Time / Update = " + std::to_string(updateTime.asMicroseconds() / numFrames) + "us");

			updateTime -= sf::seconds(1.0f);
			numFrames = 0;
		}
	}

	void Application::registerStates()
	{
		_stateStack.registerState<TitleState>(StateID::Title);
		_stateStack.registerState<MenuState>(StateID::Menu);
		_stateStack.registerState<GameState>(StateID::Game);
		_stateStack.registerState<PauseState>(StateID::Pause);
		_stateStack.registerState<GexState>(StateID::GEX);
		_stateStack.registerState<GexState>(StateID::GameOver);
	}
}

