/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#include "SoundNode.h"
#include "SoundPlayer.h"
#include <iostream>

namespace GEX
{


	SoundNode::SoundNode(SoundPlayer& player) :
			 SceneNode(),
			_soundPlayer(player)
	{
		std::cout << "SoundNode CTOR" << std::endl;
	}

	void SoundNode::playSound(SoundEffectID sound, sf::Vector2f position)
	{
		if(this->getCategory() & Category::SoundEffect)
		{
			std::cout << "Category SoundEffects " << std::endl;
			_soundPlayer.play(sound, position);
		}
	}

	unsigned int SoundNode::getCategory() const
	{
		return Category::SoundEffect;
	}
}