#include "SpriteNode.h"

namespace GEX 
{
	SpriteNode::SpriteNode(sf::Texture& texture, sf::IntRect rect) : _sprite(texture, rect)
	{}

	SpriteNode::SpriteNode(sf::Texture& texture) : _sprite(texture)
	{}

	SpriteNode::~SpriteNode()
	{}

	void SpriteNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}
}