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
#include "Vehicle.h"

#include <functional>

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

namespace GEX
{
	Direction::Direction(float a, float d) : angle(a), distance(d)
	{}

	std::map<Frog::Type, FrogData> initializeFrogData()
	{
		std::map<Frog::Type, FrogData> data;

		data[Frog::Type::Idle].hitPoints = 100;
		data[Frog::Type::Idle].texture = TextureID::Frog;
		data[Frog::Type::Idle].textureRect = sf::IntRect(61, 1, 33, 23);

		data[Frog::Type::Jumping].hitPoints = 100;
		data[Frog::Type::Jumping].texture = TextureID::Frog;
		data[Frog::Type::Jumping].textureRect = sf::IntRect(178, 62, 34, 32);

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

	std::map<Vehicle::Type, VehicleData> initializeVehicleData()
	{
		std::map<Vehicle::Type, VehicleData> data;

		data[Vehicle::Type::Car].texture = TextureID::Car;
		data[Vehicle::Type::Car].directions.push_back(Direction(-50.f, 0.f));
		data[Vehicle::Type::Car].textureRect = sf::IntRect( 1, 62, 35, 29);
		data[Vehicle::Type::Car].speed = 70.f;

		return data;
	}
}