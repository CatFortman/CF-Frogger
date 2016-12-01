#include "Entity.h"
#include "DataTables.h"
#include "TextureHolder.h"
#include "ResourceIdentifiers.h"

namespace GEX
{
	Entity::Entity(int hitpoints) :
		_velocity(),
		_angularVelocity(),
		_hitPoints(hitpoints),
		_sprite()
	{
	}

	Entity::~Entity()
	{
	}

	void Entity::setVelocity(sf::Vector2f velocity)
	{
		_velocity = velocity;
	}

	void Entity::setVelocity(float vx, float vy)
	{
		_velocity = sf::Vector2f(vx, vy);
	}

	void Entity::setPixels(sf::Vector2f pixels)
	{
		_pixels = pixels;
	}

	void Entity::setPixels(float vx, float vy)
	{
		_pixels = sf::Vector2f(vx, vy);
	}

	sf::Vector2f Entity::getPixels() const
	{
		return _pixels;
	}

	void Entity::movePlayer(sf::Vector2f pixels)
	{
		_frogMove = true;
		setPixels(pixels);
	}

	void Entity::movePlayer(float vx, float vy)
	{
		setPixels(sf::Vector2f(vx, vy));
	}

	sf::Vector2f Entity::getVelocity() const
	{
		return _velocity;
	}

	void Entity::accelerate(sf::Vector2f velocity)
	{
		setVelocity(velocity + getVelocity());
	}

	void Entity::accelerate(float vx, float vy)
	{
		setVelocity(sf::Vector2f(vx, vy) + getVelocity());
	}

	void Entity::setAngularVelocity(float av)
	{
		_angularVelocity = av;
	}

	void Entity::accelerateAngularVelocity(float av)
	{
		setAngularVelocity(av + getAngularVelocity());
	}

	float Entity::getAngularVelocity() const
	{
		return _angularVelocity;
	}

	void Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		if (_frogMove)
		{
			setPosition(getPosition() + _pixels);
			_frogMove = false;
		}
		move(_velocity * dt.asSeconds());
	}

	int Entity::getHitPoints() const
	{
		return _hitPoints;
	}

	void Entity::repair(int points)
	{
		_hitPoints += points;
	}

	void Entity::damage(int points)
	{
		_hitPoints -= points;
	}

	void Entity::destroy()
	{
		_hitPoints = 0;
	}

	bool Entity::isDestroyed() const
	{
		if (_hitPoints <= 0)
		{
			return true;
		}
		else
			return false;
	}

	sf::FloatRect Entity::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	//bool SceneNode::isMarkedForRemoval() const 
	//{
	//	// return isDestroyed()
	//}
}
