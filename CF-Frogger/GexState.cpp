#include "GexState.h"
#include "Utility.h"
#include "TextureHolder.h"
#include "FontHolder.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace GEX
{
	GexState::GexState(StateStack& stack, Context context) :
		State(stack, context),
		_backgroundSprite(),
		_gamePausedText(),
		_gexText(),
		_backspaceText(),
		_gText()
	{
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::Face);
		_backgroundSprite.setTexture(texture);
		centerOrigin(_backgroundSprite);
		_backgroundSprite.setPosition(context.window->getView().getSize() / 2.f);

		sf::Font& font = FontHolder::getInstance().get(FontID::Main);
		sf::Vector2f viewSize = context.window->getView().getSize();

		_gamePausedText.setFont(font);
		_gamePausedText.setString("Game Paused");
		_gamePausedText.setCharacterSize(70);
		centerOrigin(_gamePausedText);
		_gamePausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

		_gexText.setFont(font);
		_gexText.setString("GEX STATE");
		_gamePausedText.setCharacterSize(70);
		centerOrigin(_gexText);
		_gexText.setPosition(0.5f * viewSize.x, 0.10f * viewSize.y);

		_backspaceText.setFont(font);
		_backspaceText.setString("Press backspace to return to menu");
		_backspaceText.setCharacterSize(30);
		centerOrigin(_backspaceText);
		_backspaceText.setPosition(0.5f * viewSize.x, 0.8f * viewSize.y);

		_gText.setFont(font);
		_gText.setString("Press G to return to game");
		_gamePausedText.setCharacterSize(70);
		centerOrigin(_gText);
		_gText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
	}

	void GexState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor(sf::Color(255, 0, 0, 100));
		backgroundShape.setSize(window.getView().getSize());

		window.draw(_backgroundSprite);

		window.draw(backgroundShape);
		window.draw(_gamePausedText);
		window.draw(_gexText);
		window.draw(_backspaceText);
		window.draw(_gText);
	}

	bool GexState::update(sf::Time)
	{
		return false;
	}

	bool GexState::handleEvent(const sf::Event& event)
	{
		if (event.type != sf::Event::KeyPressed)
			return false;

		if (event.key.code == sf::Keyboard::G)
		{
			// G pressed, remove itself to return to the game
			requestStackPop();
		}

		if (event.key.code == sf::Keyboard::BackSpace)
		{
			// backspace pressed, remove itself to return to the game            requestStateClear();
			requestStackPush(StateID::Menu);
		}

		return false;
	}
}

