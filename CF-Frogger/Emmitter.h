#pragma once
#include "SceneNode.h"
#include "Partcile.h"
#include "ParticleNode.h"

namespace GEX
{
	class Emmitter : public SceneNode
	{
	public:
		explicit			Emmitter(Particle::Type type);

	private:
		void				updateCurrent(sf::Time dt, CommandQueue& commands) override;

		void				emitParticles(sf::Time dt);

	private:
		sf::Time            _accumulatedTime;
		Particle::Type		_type;
		ParticleNode*		_particleSystem;
	};
}
