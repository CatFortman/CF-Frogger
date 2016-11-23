/**
@file
@author  Cat Fortman
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once


#include "Component.h"
#include "ResourceIdentifiers.h"
#include "FontHolder.h"
#include "TextureHolder.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>


namespace GEX
{
	namespace GUI
	{
		class Button : public Component
		{
		public:
			typedef std::shared_ptr<Button>		Ptr;
			typedef std::function<void()>		Callback;


		public:
									Button();
									Button(sf::Texture& selected, sf::Texture& normal);
			void					setCallback(Callback callback);
			void					setText(const std::string& text);
			void					setToggle(bool flag);

			bool					isSelectable() const override;
			void					select() override;
			void					deselect() override;

			void					activate() override;
			void					deactivate() override;

			void					handleEvent(const sf::Event& event) override;


		private:
			void					draw(sf::RenderTarget& target, sf::RenderStates states) const override;


		private:
			Callback				_callback;          ///< onClick handler
			const sf::Texture&		_normalTexture;
			const sf::Texture&		_selectedTexture;
			const sf::Texture&		_pressedTexture;
			sf::Sprite				_sprite;
			sf::Text				_text;
			bool					_isToggle;
		};
	}
}
