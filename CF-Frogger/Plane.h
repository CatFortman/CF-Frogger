#pragma once

#include "Entity.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Animation.h"

namespace GEX 
{
	class TextNode;

	class Plane : public Entity
	{
	public:
		enum class  Type{ Eagle, Raptor, Avenger};
		
	public:
								Plane(Type type = Type::Eagle);
								//Plane(Planes type, const TextureHolder& textures);

		virtual					~Plane() {};

		unsigned int			getCategory() const override;

		sf::FloatRect			getBoundingRect() const override;

		float					getMaxSpeed() const;

		bool					isAllied() const;
		bool					isMarkedForRemoval() const;

	private:
		void					drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;
		void					updateCurrent(sf::Time dt, CommandQueue& commands);
		void					updateTexts();
		void					movementUpdate(sf::Time dt);


	private:

		Type					_type;
		sf::Sprite				_sprite;
		TextNode*				_healthDisplay;
		int						_directionIndex;
		float					_travelDistance;

		bool					_isMarkedForRemoval;
	};

}