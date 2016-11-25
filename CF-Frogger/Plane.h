#pragma once

#include "Entity.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Animation.h"

namespace GEX 
{
	class TextNode;

	class Frog : public Entity
	{
	public:
		enum class  Type{ Frogger};
		
	public:
								Frog(Type type = Type::Frogger);
								//Frog(Frogs type, const TextureHolder& textures);

		virtual					~Frog() {};

		unsigned int			getCategory() const override;

		sf::FloatRect			getBoundingRect() const override;

		bool					isAllied() const;
		bool					isMarkedForRemoval() const;

	private:
		void					drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;
		void					updateCurrent(sf::Time dt, CommandQueue& commands);
		void					movementUpdate(sf::Time dt);
		void					updateTexts();


	private:

		TextNode*				_healthDisplay;
		Type					_type;
		sf::Sprite				_sprite;
		int						_directionIndex;
		float					_travelDistance;

		bool					_isMarkedForRemoval;
	};

}