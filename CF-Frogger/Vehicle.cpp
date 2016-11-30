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
		return TextureID::Frog;
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
		return Category::playerCharacter;
	}

	sf::FloatRect Vehicle::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void Vehicle::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Vehicle::movementUpdate(sf::Time dt)
	{
	}

	void Vehicle::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		// check if Idle died
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
