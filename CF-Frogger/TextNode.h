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
#include "SceneNode.h"
#include "SFML\Graphics\Text.hpp"
#include <string>

namespace GEX
{
	class TextNode : public SceneNode
	{
	public:
		explicit TextNode(const std::string text);
		void setText(const std::string& text);

	private:
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

		sf::Text _text;
	};
}
