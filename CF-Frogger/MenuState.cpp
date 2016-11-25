#include "MenuState.h"
#include "MenuState.h"
#include "Utility.h"
#include "TextureHolder.h"
#include "FontHolder.h"
#include "MusicPlayer.h"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"

namespace GEX
{
	MenuState::MenuState(StateStack& stack, Context context) :
		State(stack, context),
		_mBackgroundSprite(),
		_mGUIContainer()
	{
		_mBackgroundSprite.setTexture(TextureHolder::getInstance().get(TextureID::MenuScreen));
		_mBackgroundSprite.setScale(1.5, 1.25);

		auto gPlayButton = std::make_shared<GUI::Button>(TextureHolder::getInstance().get(TextureID::GreenPlay), TextureHolder::getInstance().get(TextureID::RedPlay));
		gPlayButton->setPosition(145.f,400.f);
		gPlayButton->setCallback([this]()
		{
			requestStackPop();
			requestStackPush(StateID::Game);
		});
		_mGUIContainer.pack(gPlayButton);

		auto rQuitButton = std::make_shared<GUI::Button>(TextureHolder::getInstance().get(TextureID::GreenQuit), TextureHolder::getInstance().get(TextureID::RedQuit));
		rQuitButton->setPosition(gPlayButton->getPosition() + sf::Vector2f(0.f, 55.f));
		rQuitButton->setCallback([this]()
		{
			requestStackPop();
		});

		_mGUIContainer.pack(rQuitButton);

		context.music->play(MusicID::MenuTheme);
	}

	void MenuState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());
		window.draw(_mBackgroundSprite);
		window.draw(_mGUIContainer);
	}

	bool MenuState::update(sf::Time)
	{
		return true;
	}

	bool MenuState::handleEvent(const sf::Event& event)
	{
		// The demonstration menu logic
		/*if (event.type != sf::Event::KeyPressed)
			return false;*/
		_mGUIContainer.handleEvent(event);    
		return false;
	}
}
