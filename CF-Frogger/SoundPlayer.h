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