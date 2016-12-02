#include "Vehicle.h"
#include "TextureHolder.h"
#include "ResourceIdentifiers.h"
#include "TextNode.h"
#include "Utility.h"
#include "DataTables.h"

#include <cassert>
namespace GEX
{
	const std::map<Vehicle::Type, VehicleData> table = initializeVehicleData();

	TextureID toTextureID(Vehicle::Type type)
	{
		switch (type) {
		case Vehicle::Type::Car:
			return TextureID::Car;
		case Vehicle::Type::RaceCarL:
			return TextureID::RaceCarL;
		case Vehicle::Type::RaceCarR:
			return TextureID::RaceCarR;
		case Vehicle::Type::Tractor:
			return TextureID::Tractor;
		case Vehicle::Type::Truck:
			return TextureID::Truck;
		}
		return TextureID::Car;
	}

	Vehicle::Vehicle(Type type) :
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

	unsigned int Vehicle::getCategory() const
	{
		switch (_type)
		{
		case GEX::Vehicle::Type::Car:
			return Category::vehicle;
			break;
		case GEX::Vehicle::Type::RaceCarR:
			return Category::vehicle;
			break;
		case GEX::Vehicle::Type::RaceCarL:
			return Category::vehicle;
			break;
		case GEX::Vehicle::Type::Tractor:
			return Category::vehicle;
			break;
		case GEX::Vehicle::Type::Truck:
			return Category::vehicle;
			break;
		default:
			assert(0); //missing type
			break;
		}
		return Category::none;
}

sf::FloatRect Vehicle::getBoundingRect() const
{
	return getWorldTransform().transformRect(_sprite.getGlobalBounds());
}

void Vehicle::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(_sprite, state);
}

float Vehicle::getMaxSpeed() const
{
	return table.at(_type).speed;
}

void Vehicle::movementUpdate(sf::Time dt)
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

void Vehicle::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (isDestroyed())
	{
		return;
	}

	movementUpdate(dt);
	Entity::updateCurrent(dt, commands);
}

bool Vehicle::isMarkedForRemoval() const
{
	return isDestroyed();
}
}
