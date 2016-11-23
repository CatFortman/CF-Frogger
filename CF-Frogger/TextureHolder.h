#pragma once

#include "ResourceIdentifiers.h"

#include <SFML\Graphics\Texture.hpp>
#include <memory>
#include <map>

namespace GEX
{
	class TextureHolder
	{
	public:
		static TextureHolder& getInstance();
		
		void load(TextureID id, const std::string& path);
		sf::Texture& get(TextureID);	
		
	private:
		TextureHolder();
		static TextureHolder* _instance;
		
		std::map<TextureID, std::unique_ptr<sf::Texture>> _textures;
	};
}
