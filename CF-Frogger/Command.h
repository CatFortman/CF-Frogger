#pragma once
#include <cassert>
#include "SFML/System/Time.hpp"
#include <functional>
namespace GEX {
	class SceneNode;
	class Command
	{
	public:
		Command();
		std::function<void(SceneNode&, sf::Time)> action;
		unsigned int							  category;
	};

	template <typename GameObject, typename function>
	std::function<void(SceneNode&, sf::Time)>derivedAction(function fn)
	{
		return[=](SceneNode& node, sf::Time dt)
		{
			assert(dynamic_cast<GameObject*>(&node) != nullptr); //if it cant downcast to that it crashes
			//downcasting
			fn(static_cast<GameObject&>(node), dt);
		};
	}
}

