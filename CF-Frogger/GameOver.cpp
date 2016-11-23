#include "GameOver.h"
#include "Utility.h"
#include "TextureHolder.h"
#include "FontHolder.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace GEX
{
	GameOverState::GameOverState(StateStack& stack, Context context) :
		State(stack, context),
		_gameOverText(),
		_elapsedTime(sf::Time::Zero)
	{
		sf::Font& font = FontHolder::getInstance().get(FontID::Main);
		sf::Vector2f windowSize(context.window->getView().getSize());

		_gameOverText.setFont(font);
		if (context.player->getMissionStatus() == MissionStatus::Fail)
		{
			_gameOverText.setString("Mission Failed!");
		}
		else
		{
			_gameOverText.setString("Mission Success!");
		}

		_gameOverText.setCharacterSize(70);
		centerOrigin(_gameOverText);
		_gameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
	}

	void GameOverState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
		backgroundShape.setSize(window.getView().getSize());

		window.draw(_gameOverText);
	}

	bool GameOverState::update(sf::Time dt)
	{
		// 3 second count down
		_elapsedTime += dt;
		if (_elapsedTime > sf::seconds(3))
		{
			requestStateClear();
			requestStackPush(StateID::Menu);
		}

		return false;
	}

	bool GameOverState::handleEvent(const sf::Event& event)
	{
		if (event.type != sf::Event::KeyPressed)
			return false;

		if (event.key.code == sf::Keyboard::Escape)
		{
			// Escape pressed, remove itself to return to the game
			requestStackPop();
		}

		if (event.key.code == sf::Keyboard::BackSpace)
		{
			// Escape pressed, remove itself to return to the game            requestStateClear();
			requestStackPush(StateID::Menu);
		}

		return false;
	}
}
