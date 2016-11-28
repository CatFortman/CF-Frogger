#pragma once
#include "SceneNode.h"
#include "CommandQueue.h"

namespace GEX 
{
	class Entity : public SceneNode
	{
	public:
		Entity(int hitpoints = 100);
		virtual ~Entity();

		void			setVelocity(sf::Vector2f velocity);
		void			setVelocity(float vx, float vy);
		sf::Vector2f	getVelocity() const;

		void            movePlayer();

		void			accelerate(sf::Vector2f velocity);
		void			accelerate(float vx, float vy);

		void			setAngularVelocity(float av);
		float			getAngularVelocity() const;

		void			accelerateAngularVelocity(float av);

		int			    getHitPoints() const;
		void			repair(int points);
		void			damage(int points);

		void			destroy();
		bool			isDestroyed() const override;
		/*bool			isMarkedForRemoval() const override;*/

		sf::FloatRect	getBoundingRect() const;

	protected:
		void			updateCurrent(sf::Time dt, CommandQueue& commands) override;

	private:
		sf::Sprite		_sprite;

		float           _pixels;
		float			_angularVelocity;
		sf::Vector2f	_velocity;
		int				_hitPoints;
	};
}

