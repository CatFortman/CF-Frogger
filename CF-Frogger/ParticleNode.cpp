#include "ParticleNode.h"
#include "TextureHolder.h"
#include "ResourceIdentifiers.h"
#include "DataTables.h"

namespace GEX
{
	const std::map<Particle::Type, ParticleData> Table = initializeParticleData();

	ParticleNode::ParticleNode(Particle::Type type) :
		_particles(),
		_texture(TextureHolder::getInstance().get(TextureID::Particle)),
		_type(type),
		_vertexArray(sf::Quads),
		_needsVertexUpdate(true)
	{

	}

	void ParticleNode::addParticle(sf::Vector2f position)
	{
		Particle particle;
		particle.position = position;
		particle.color = Table.at(_type).color;
		particle.lifetime = Table.at(_type).lifetime;

		_particles.push_back(particle);
	}

	Particle::Type ParticleNode::getParticleType() const
	{
		return _type;
	}

	unsigned int ParticleNode::getCategory() const
	{
		return Category::ParticleSystem;
	}

	void ParticleNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		if (_needsVertexUpdate)
		{
			computeVertices();
			_needsVertexUpdate = false;
		}

		state.texture = &_texture; // refernce to particle texture

		target.draw(_vertexArray, state);
	}

	void ParticleNode::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		// remove expired particles
		while (!_particles.empty() && _particles.front().lifetime <= sf::Time::Zero)
		{
			_particles.pop_front();
		}

		// update 
		for (auto& particle : _particles)
		{
			particle.lifetime -= dt;
		}

		_needsVertexUpdate = true;
	}

	void ParticleNode::addVertex(float worldx, float worldy, float textu, float textv, const sf::Color& color) const
	{
		sf::Vertex vertex;
		vertex.position = sf::Vector2f(worldx, worldy);
		vertex.texCoords = sf::Vector2f(textu, textv);
		vertex.color = color;

		_vertexArray.append(vertex);
	}

	void ParticleNode::computeVertices() const
	{
		sf::Vector2f size(_texture.getSize());
		sf::Vector2f half = size / 2.f;

		// refill vertex array
		_vertexArray.clear();
		for (const auto& particle : _particles)
		{
			sf::Vector2f pos = particle.position;
			sf::Color color = particle.color;

			float ratio = particle.lifetime.asSeconds()
				/ Table.at(_type).lifetime.asSeconds();

			color.a = static_cast<sf::Uint8>(255 * std::max(ratio, 0.f));

			// add 4 vertices to make up a rectangle primative for particle
			addVertex(pos.x - half.x, pos.y - half.y, 0.f, 0.f, color);
			addVertex(pos.x + half.x, pos.y - half.y, size.x, 0.f, color);
			addVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, color);
			addVertex(pos.x - half.x, pos.y + half.y, 0.f, size.y, color);
		}
	}
}