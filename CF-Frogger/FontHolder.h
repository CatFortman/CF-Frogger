#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Font.hpp"
#include "ResourceIdentifiers.h"

#include <memory>
#include <map>

namespace GEX
{
	class FontHolder
	{
	private:
		FontHolder() {};    // must use getInstance()  
	public:
		static FontHolder&                              getInstance(); // factory method

		void                                            load(FontID id, const std::string& path);
		sf::Font&                                       get(FontID) const;

	private:
		static FontHolder*                              _instance;

		std::map<FontID, std::unique_ptr<sf::Font>>     _fonts;
	};
}


