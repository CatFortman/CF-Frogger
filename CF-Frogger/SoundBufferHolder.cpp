#include "SoundBufferHolder.h"
/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#include "SoundBufferHolder.h"
#include <cassert>

namespace GEX
{
	SoundBufferHolder* SoundBufferHolder::_instance = nullptr;

	SoundBufferHolder& SoundBufferHolder::getInstance()
	{
		if (!SoundBufferHolder::_instance)
			SoundBufferHolder::_instance = new SoundBufferHolder();

		return *SoundBufferHolder::_instance;
	}

	void SoundBufferHolder::load(SoundEffectID id, const std::string & path)
	{
		std::unique_ptr<sf::SoundBuffer> texture(new sf::SoundBuffer);
		if (!texture->loadFromFile(path))
			throw std::runtime_error("Load failed - " + path);

		auto rc = _soundEffects.insert(std::make_pair(id, std::move(texture)));
		if (!rc.second)
		  assert(0); // big problems if insert fails
	}

	sf::SoundBuffer& SoundBufferHolder::get(SoundEffectID id) const
	{
		auto found = _soundEffects.find(id);
		assert(found != _soundEffects.end());  // find returns an iterator to pair in map

		return *found->second; // de-reference iterator and return pointer by reference
	}

}
