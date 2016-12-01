#include "RiverObject.h"
#include "TextureHolder.h"
#include "ResourceIdentifiers.h"
#include "TextNode.h"
#include "Utility.h"
#include "DataTables.h"

#include <cassert>
namespace GEX
{
	const std::map<RiverObject::Type, RiverObjectData> table = initializeRiverObjectData();

	TextureID toTextureID(RiverObject::Type type)
	{
		return TextureID::tree1;
	}

	RiverObject::RiverObject(Type type) :
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect),
		_directionIndex(0),
		_isMarkedForRemoval(false)
	{
		// set up the animation
		centerOrigin(_sprite);

		// TextureHolder::getInstance().load(TextureID::AIRFrog, "../media/Textures/Idles.png");
		sf::FloatRect bounds = _sprite.getLocalBounds();
		_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	unsigned int RiverObject::getCategory() const
	{
		switch (_type)
		{
		case GEX::RiverObject::Type::turtles1:
			return Category::turtles;
			break;
		case GEX::RiverObject::Type::turtles2:
			return Category::turtles;
			break;
		case GEX::RiverObject::Type::turtles3:
			return Category::turtles;
			break;
		case GEX::RiverObject::Type::turtles4:
			return Category::turtles;
			break;
		case GEX::RiverObject::Type::threeTurtles1:
			return Category::turtles;
			break;
		case GEX::RiverObject::Type::threeTurtles2:
			return Category::turtles;
			break;
		case GEX::RiverObject::Type::threeTurtles3:
			return Category::turtles;
			break;
		case GEX::RiverObject::Type::threeTurtles4:
			return Category::turtles;
			break;
		case GEX::RiverObject::Type::tree1:
			return Category::logs;
			break;
		case GEX::RiverObject::Type::tree2:
			return Category::logs;
			break;
		default:
			assert(0); //missing type
			break;
		}
		return Category::none;
	}

	sf::FloatRect RiverObject::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void RiverObject::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	float RiverObject::getMaxSpeed() const
	{
		return table.at(_type).speed;
	}

	void RiverObject::movementUpdate(sf::Time dt)
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

	void RiverObject::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		if (isDestroyed())
		{
			return;
		}

		movementUpdate(dt);
		Entity::updateCurrent(dt, commands);
	}

	bool RiverObject::isMarkedForRemoval() const
	{
		return isDestroyed();
	}
}

