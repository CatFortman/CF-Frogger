/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once

#include <SFML/Graphics/Text.hpp>

#include "Component.h"
#include "ResourceIdentifiers.h"
#include "FontHolder.h"

namespace GEX
{
	namespace GUI
	{
		class Label : public Component
		{
		public:
			typedef std::shared_ptr<Label> Ptr;


		public:
								Label(const std::string& text);

			virtual bool		isSelectable() const;
			void				setText(const std::string& text);
			void				setCharacterSize(unsigned int size);

			void centerOrigin();

			virtual void		handleEvent(const sf::Event& event);


		private:
			void				draw(sf::RenderTarget& target, sf::RenderStates states) const;


		private:
			sf::Text			_text;
		};
	}
}