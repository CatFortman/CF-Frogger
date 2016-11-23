#include "TextureHolder.h"
#include <iostream>
#include <cassert>
#include <memory>

namespace GEX 
{
	TextureHolder* TextureHolder::_instance = nullptr;
	TextureHolder::TextureHolder()
	{}
	TextureHolder & TextureHolder::getInstance()
	{
		if (!TextureHolder::_instance) // lazy instantiation only constructs when called for
			TextureHolder::_instance = new TextureHolder();

		return *TextureHolder::_instance;
	}

	void TextureHolder::load(TextureID id,const std::string & path)
	{
		std::unique_ptr<sf::Texture> texture(new sf::Texture);

		if (!texture->loadFromFile(path))
		{
			std::cout << "load failed!" << std::endl;
			assert(0);
		}
		auto rc = _textures.insert(std::make_pair(id, std::move(texture)));
		if (!rc.second)
			assert(0);
	}

	sf::Texture& GEX::TextureHolder::get(TextureID tID)
	{

		auto found = _textures.find(tID);
		assert(found != _textures.end());

		return *found->second;
	}
}