#include "Plane.h"
#include "TextureHolder.h"
#include "ResourceIdentifiers.h"
#include "TextNode.h"
#include "Utility.h"
#include "DataTables.h"

#include <cassert>
namespace GEX 
{
	const std::map<Plane::Type, AircraftData> table = initializeAircraftData();

	TextureID toTextureID(Plane::Type type)
	{
		return TextureID::Frog;
	}

	Plane::Plane(Type type) :
		Entity(table.at(type).hitPoints),
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect),
		_directionIndex(0),

		_isMarkedForRemoval(false)
	{
		// set up the animation

		centerOrigin(_sprite);
		//
		// build fire and launch commands
		//
		
		//
		// build mini-HUD for aircraft
		//

		// TextureHolder::getInstance().load(TextureID::AIRPLANE, "../media/Textures/eagles.png");
		sf::FloatRect bounds = _sprite.getLocalBounds();
		_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

		std::unique_ptr<TextNode> healthDisplay(new TextNode(std::to_string(getHitPoints()) + "HP"));
		_healthDisplay = healthDisplay.get();
		healthDisplay->setPosition(0.f, 50.f);
		attatchChild(std::move(healthDisplay));
	}

	unsigned int Plane::getCategory() const
	{
		switch (_type)
		{
		case GEX::Plane::Type::Eagle:
		default:
			assert(0); //missing type
			break;

		}
		return Category::none;
	}

	sf::FloatRect Plane::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void Plane::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Plane::movementUpdate(sf::Time dt)
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

	void Plane::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		// normalize speed
		// needed when travelling diagonl
		sf::Vector2f velo = getVelocity();
		if (velo.x != 0.f && velo.y != 0.f)
			setVelocity(velo / std::sqrt(2.f));

		if (isDestroyed())
		{
			// drop a pickup??
			return;
		}

		movementUpdate(dt);
		Entity::updateCurrent(dt, commands);

		updateTexts();
	}

	void Plane::updateTexts()
	{
		_healthDisplay->setText(std::to_string(getHitPoints()) + "HP");
		_healthDisplay->setPosition(0.f, 50.f);
		_healthDisplay->setRotation(-getRotation());
	}

	float Plane::getMaxSpeed() const
	{
		return table.at(_type).speed;
	}

	bool Plane::isAllied() const
	{
		return _type == Type::Eagle;
	}

	bool Plane::isMarkedForRemoval() const
	{
		return isDestroyed();
	}
}