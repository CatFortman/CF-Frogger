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
		enum class  Type{ Idle, Jumping, Die1, Die2, Die3};
		
	public:
								Frog(Type type = Type::Idle);
								//Frog(Frogs type, const TextureHolder& textures);

		virtual					~Frog() {};

		unsigned int			getCategory() const override;

		sf::FloatRect			getBoundingRect() const override;

		bool					isMarkedForRemoval() const;
		void					adjustFrogLives();
		void					setIsDying(bool dying);
		bool					isDying();

		void					setIsRespawning(bool dying);
		bool					isRespawing();

		void					isJumping(bool jumping);
		void					checkIfJumping();

		void					playDeathAnimation();

		void					setType(Frog::Type type);

	private:
		void					drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;
		void					updateCurrent(sf::Time dt, CommandQueue& commands);
		void					movementUpdate(sf::Time dt);
		void					updateTexts();

	private:

		TextNode*				_healthDisplay;
		Type					_type;
		sf::Sprite				_sprite;

		sf::Clock				_deathTimer;

		bool				    _respawning;
		bool					_dying;
		bool					_jumping;
		int						_jumpTimer;

		int						_directionIndex;
		float					_travelDistance;

		bool					_isMarkedForRemoval;

		int						_points;
	};

}