/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#include "Button.h"
#include "Utility.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>



namespace GEX 
{
	namespace GUI
	{

		Button::Button() : 
			_callback(),
			_normalTexture(TextureHolder::getInstance().get(TextureID::ButtonNormal)),
			_selectedTexture(TextureHolder::getInstance().get(TextureID::ButtonSelected)),
			_pressedTexture(TextureHolder::getInstance().get(TextureID::ButtonPressed)),
			_sprite(),
			_text("", FontHolder::getInstance().get(FontID::Main), 20),
			_isToggle(false)
		{
			_sprite.setTexture(_normalTexture);
			_sprite.setTextureRect(sf::IntRect(0, 0, 200, 50));

			sf::FloatRect bounds = _sprite.getLocalBounds();
			_text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
		}

		Button::Button(sf::Texture& selected, sf::Texture& normal) :
			_callback(),
			_normalTexture(normal),
			_selectedTexture(selected),
			_pressedTexture(selected),
			_sprite(),
			_text("", FontHolder::getInstance().get(FontID::Main), 20),
			_isToggle(false)
		{
			_sprite.setTexture(normal);

			sf::FloatRect bounds = _sprite.getLocalBounds();
			_text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
		}
		void Button::setCallback(Callback callback)
		{
			_callback = std::move(callback);
		}

		void Button::setText(const std::string& text)
		{
			_text.setString(text);
			centerOrigin(_text);
		}

		void Button::setToggle(bool flag)
		{
			_isToggle = flag;
		}

		bool Button::isSelectable() const
		{
			return true;
		}

		void Button::select()
		{
			Component::select();

			_sprite.setTexture(_selectedTexture);
		}

		void Button::deselect()
		{
			Component::deselect();

			_sprite.setTexture(_normalTexture);
		}

		void Button::activate()
		{
			Component::activate();

			// If we are toggle then we should show that the button is pressed and thus "toggled".
			if (_isToggle)
				_sprite.setTexture(_pressedTexture);

			if (_callback)
				_callback();

			// If we are not a toggle then deactivate the button since we are just momentarily activated.
			if (!_isToggle)
				deactivate();
		}

		void Button::deactivate()
		{
			Component::deactivate();

			if (_isToggle)
			{
				// Reset texture to right one depending on if we are selected or not.
				if (isSelected())
					_sprite.setTexture(_selectedTexture);
				else
					_sprite.setTexture(_normalTexture);
			}
		}

		void Button::handleEvent(const sf::Event&)
		{}

		void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();
			target.draw(_sprite, states);
			target.draw(_text, states);
		}
	}
}
