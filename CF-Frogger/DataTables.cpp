/**
@file
@author  Cat Fortman
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#include "DataTables.h"
#include "Plane.h"
#include "ParticleNode.h"

#include <functional>

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

namespace GEX
{
	Direction::Direction(float a, float d) : angle(a), distance(d)
	{}

	std::map<Plane::Type, AircraftData> initializeAircraftData()
	{
		std::map<Plane::Type, AircraftData> data;

		

		return data;
	}

	std::map<Particle::Type, ParticleData> initializeParticleData()
	{
		std::map<Particle::Type, ParticleData> data;

		data[Particle::Type::propellant].color = sf::Color(255, 255, 50);
		data[Particle::Type::propellant].lifetime = sf::seconds(0.6f);

		data[Particle::Type::smoke].color = sf::Color(50, 50, 50);
		data[Particle::Type::smoke].lifetime = sf::seconds(4.f);

		return data;
	}
}