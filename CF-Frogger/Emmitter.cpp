#include "Emmitter.h"


namespace GEX
{
	Emmitter::Emmitter(Particle::Type type) :
		_accumulatedTime(sf::Time::Zero),
		_type(type),
		_particleSystem(nullptr)
	{

	}

	void Emmitter::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		if (_particleSystem)
		{
			emitParticles(dt);
		}
		else
		{
			auto finder = [this](ParticleNode& container, sf::Time dt)
			{
				if (container.getParticleType() == _type)
				{
					_particleSystem = &container;
				}
			};

			Command command;
			command.category = Category::ParticleSystem;
			command.action = derivedAction<ParticleNode>(finder);

			commands.push(command);
		}
	}

	void Emmitter::emitParticles(sf::Time dt)
	{
		const float emissionRate = 300.f;
		const sf::Time interval = sf::seconds(1) / emissionRate;

		_accumulatedTime += dt;
		while (_accumulatedTime > interval)
		{
			_accumulatedTime = -interval;
			_particleSystem->addParticle(getWorldPosition());
		}
	}

}