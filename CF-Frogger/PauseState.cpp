#include "PauseState.h"
#include "PauseState.h"
#include "Utility.h"
#include "TextureHolder.h"
#include "FontHolder.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace GEX
{
	PauseState::PauseState(StateStack& stack, Context context) :
		State(stack, context),
		_backgroundSprite(),
		_pausedText(),
		_instructionText()
	{
		sf::Font& font = FontHolder::getInstance().get(FontID::Main);
		sf::Vector2f viewSize = context.window->getView().getSize();

		_pausedText.setFont(font);
		_pausedText.setString("Game Paused");
		_pausedText.setCharacterSize(70);
		centerOrigin(_pausedText);
		_pausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

		_instructionText.setFont(font);
		_instructionText.setString("(Press Backspace to return to the main menu)");
		centerOrigin(_instructionText);
		_instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
	}

	void PauseState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
		backgroundShape.setSize(window.getView().getSize());

		window.draw(backgroundShape);
		window.draw(_pausedText);
		window.draw(_instructionText);
	}

	bool PauseState::update(sf::Time)
	{
		return false;
	}

	bool PauseState::handleEvent(const sf::Event& event)
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
