#pragma once

#include "Entity.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Animation.h"

namespace GEX
{
	class TextNode;

	class Vehicle : public Entity
	{
	public:
		enum class  Type { Car, RaceCarL, RaceCarR, Tractor, Truck};

	public:
		Vehicle(Type type = Type::Car);
		//Frog(Frogs type, const TextureHolder& textures);

		virtual					~Vehicle() {};

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
