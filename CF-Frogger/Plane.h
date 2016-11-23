#pragma once

#include "Entity.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Animation.h"
#include "SoundNode.h"
#include "Utility.h"
#include "Animation.h"
#include "Animation2.h"
#include "JsonFrameParser.hpp"

#include <map>

namespace GEX 
{
	class TextNode;

	class Cat : public Entity
	{
	public:
		enum class  Type{ Cat};
		enum class  State { Walk, Idle, Dead, Attack };
		
	public:
								Cat(Type type = Type::Cat);
								//Plane(Planes type, const TextureHolder& textures);

		virtual					~Cat() {};

		unsigned int			getCategory() const override;

		sf::FloatRect			getBoundingRect() const override;

		float					getMaxSpeed() const;

		void					playLocalSound(CommandQueue& commands, SoundEffectID effectID);

	private:
		void					drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;
		void					updateCurrent(sf::Time dt, CommandQueue& commands);
		void					updateTexts();
		void					movementUpdate(sf::Time dt);

	private:

		Type												_type;
		sf::Sprite											_sprite;
		State												_state;
		TextNode*											_healthDisplay;
		std::map<State, std::unique_ptr<Animation2>>        _animations;
		int													_directionIndex;
		float												_travelDistance;

	};

}