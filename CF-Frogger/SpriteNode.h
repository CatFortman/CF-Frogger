#pragma once
#include "SceneNode.h"

namespace GEX
{
	class SpriteNode : public SceneNode
	{
	public:
		SpriteNode( sf::Texture&, sf::IntRect);
		SpriteNode(sf::Texture&);
		~SpriteNode();
	private:

		void drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;

	private:
		sf::Sprite _sprite;
	};
}

