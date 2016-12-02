#pragma once

#include "Entity.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Animation.h"

namespace GEX
{
	class TextNode;

	class RiverObject : public Entity
	{
	public:
		enum class  Type { tree1, tree2, turtles1, turtles2, turtles3, turtles4, threeTurtles1, threeTurtles2, threeTurtles3, threeTurtles4};

	public:
		RiverObject(Type type = Type::tree1);
		//Frog(Frogs type, const TextureHolder& textures);

		virtual					~RiverObject() {};

		unsigned int			getCategory() const override;

		float					getMaxSpeed() const;

		sf::FloatRect			getBoundingRect() const override;

		bool					isMarkedForRemoval() const;

	private:
		void					drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;
		void					updateCurrent(sf::Time dt, CommandQueue& commands);
		void					movementUpdate(sf::Time dt);

	private:

		Type					_type;
		sf::Sprite				_sprite;

		int						_directionIndex;
		float					_travelDistance;

		bool					_isMarkedForRemoval;
	};

}
