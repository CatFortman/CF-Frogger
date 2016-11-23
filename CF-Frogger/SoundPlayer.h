/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION

The SceneNode class is the base class for any object that is to be put in the scene graph. Wich means any game
objects including background, Non-Player-Objects (NPOs), and the player object.
*/

#pragma once

#include "ResourceIdentifiers.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "SoundBufferHolder.h"
#include <list>


namespace GEX
{
	class SoundPlayer
	{
	public:
									SoundPlayer();
									SoundPlayer(const SoundPlayer&) = delete;    ///< non-copyable 
		SoundPlayer&				operator =(const SoundPlayer&) = delete;	 ///< non-copyable 
		
		void						play(SoundEffectID effect);
		void						play(SoundEffectID effect, sf::Vector2f position);

		void						removeStoppedSounds();
		void						setListenerPosition(sf::Vector2f position);
		sf::Vector2f				getListenerPosition() const;

	private:
		std::list<sf::Sound>		_sounds;
	};
}