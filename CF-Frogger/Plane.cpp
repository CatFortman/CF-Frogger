#include "Plane.h"
#include "TextureHolder.h"
#include "ResourceIdentifiers.h"
#include "TextNode.h"
#include "Utility.h"
#include "DataTables.h"

#include <cassert>
namespace GEX 
{
	const std::map<Cat::Type, CatData> table = initializeCatData();

	TextureID toTextureID(Cat::Type type)
	{
		switch (type) {
		case Cat::Type::Cat:
			return TextureID::Cat;
		}
		return TextureID::Cat;
	}

	Cat::Cat(Type type) :
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect),
		_directionIndex(0)
	{
		centerOrigin(_sprite);
		// set up the animation
		JsonFrameParser* frames = new JsonFrameParser("Media/Zombie.json");
		_animations[State::Walk] = std::unique_ptr<Animation2>(new Animation2());
		_animations[State::Walk]->addFrameSet(frames->getFramesFor("walk"));
		//_animations[State::MoveBack]->addFrame({ 45,0,45,0 });
		_animations[State::Walk]->setDurationAsSeconds(1.f);
		_sprite.setTextureRect(_animations[State::Walk]->getFrameByNumber(0));
	}

	unsigned int Cat::getCategory() const
	{
		switch (_type)
		{
		case GEX::Cat::Type::Cat:
			return Category::playerCharacter;
			break;
		default:
			assert(0); //missing type
			break;

		}
		return Category::none;
	}

	sf::FloatRect Cat::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void Cat::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Cat::movementUpdate(sf::Time dt)
	{
		const std::vector<Direction>& directions = table.at(_type).directions;
		if (!directions.empty())
		{
			float distanceToTravel = directions.at(_directionIndex).distance;
			if (_travelDistance > distanceToTravel)
			{
				_directionIndex = (_directionIndex + 1) % directions.size();
				_travelDistance = 0;
			}
			_travelDistance += getMaxSpeed() * dt.asSeconds();
			float dirAngle = directions.at(_directionIndex).angle + 90.f;
			float vx = getMaxSpeed() * GEX::cos(dirAngle);
			float vy = getMaxSpeed() * GEX::sin(dirAngle);
			setVelocity(vx, vy);
		}
	}

	void Cat::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		// update animation
		_sprite.setTextureRect(_animations.at(_state)->update(dt));

		// normalize speed
		movementUpdate(dt);
		Entity::updateCurrent(dt, commands);

		updateTexts();
	}

	void Cat::updateTexts()
	{
		_healthDisplay->setText(std::to_string(getHitPoints()) + "HP");
		_healthDisplay->setPosition(0.f, 50.f);
		_healthDisplay->setRotation(-getRotation());
	}

	float Cat::getMaxSpeed() const
	{
		return table.at(_type).speed;
	}

	void Cat::playLocalSound(CommandQueue& commands, SoundEffectID effectID)
	{
		sf::Vector2f worldPosition = getWorldPosition();

		Command command;
		command.category = Category::SoundEffect;
		command.action = derivedAction<SoundNode>(
			[effectID, worldPosition](SoundNode& node, sf::Time)
		{
			node.playSound(effectID, worldPosition);
		});

		commands.push(command);
	}
}