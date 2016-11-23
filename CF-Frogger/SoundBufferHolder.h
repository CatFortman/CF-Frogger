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



#include <memory>
#include <map>
#include <SFML/Audio/SoundBuffer.hpp>
#include "ResourceIdentifiers.h"

namespace GEX
{


	class SoundBufferHolder
	{
	public:
		static SoundBufferHolder&				getInstance(); // factory method

		void                                    load(SoundEffectID id, const std::string& path);
		sf::SoundBuffer&						get(SoundEffectID) const;

	private:
												SoundBufferHolder() {};      // must use getInstance() to get it

	private:
		static SoundBufferHolder*				_instance;  ///< single instance of class

		std::map<
			SoundEffectID, 
			std::unique_ptr<sf::SoundBuffer>
		>										_soundEffects;
	};
}