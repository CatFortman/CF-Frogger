/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "Label.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GEX
{
	namespace GUI
	{
		Label::Label(const std::string& text) :
			_text(text, FontHolder::getInstance().get(FontID::Main), 48)
		{}

		bool Label::isSelectable() const
		{
			return false;
		}

		void Label::handleEvent(const sf::Event&)
		{}

		void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();
			target.draw(_text, states);
		}

		void Label::setText(const std::string& text)
		{
			_text.setString(text);
		}

		void Label::setCharacterSize(unsigned int size)
		{
			_text.setCharacterSize(size);
		}

		void Label::centerOrigin()
		{
			sf::FloatRect bounds = _text.getLocalBounds();
			_text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));

		}
	}
}