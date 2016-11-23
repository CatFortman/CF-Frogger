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

#include "SceneNode.h"
#include "ResourceIdentifiers.h"

namespace GEX
{

	class SoundPlayer;

	class SoundNode : public SceneNode
	{
	public:
		explicit				SoundNode(SoundPlayer& player);
		void					playSound(SoundEffectID sound, sf::Vector2f position);

		unsigned int			getCategory() const override;


	private:
		SoundPlayer&			_soundPlayer;
	};
}

