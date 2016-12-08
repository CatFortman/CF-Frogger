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
#include "RiverObject.h"

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

		data[Frog::Type::Die1].hitPoints = 0;
		data[Frog::Type::Die1].texture = TextureID::Frog;
		data[Frog::Type::Die1].textureRect = sf::IntRect(108, 100, 29, 38);

		data[Frog::Type::Die2].hitPoints = 0;
		data[Frog::Type::Die2].texture = TextureID::Frog;
		data[Frog::Type::Die2].textureRect = sf::IntRect(357, 100, 36, 40);

		data[Frog::Type::Die3].hitPoints = 0;
		data[Frog::Type::Die3].texture = TextureID::Frog;
		data[Frog::Type::Die3].textureRect = sf::IntRect(283, 100, 34, 40);
		
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

	std::map<RiverObject::Type, RiverObjectData> initializeRiverObjectData()
	{
		std::map<RiverObject::Type, RiverObjectData> data;

		data[RiverObject::Type::tree1].texture = TextureID::tree1;
		data[RiverObject::Type::tree1].directions.push_back(Direction(-91.f, 0.f));
		data[RiverObject::Type::tree1].textureRect = sf::IntRect(198, 31, 93, 29);
		data[RiverObject::Type::tree1].speed = 70.f;

		data[RiverObject::Type::tree2].texture = TextureID::tree2;
		data[RiverObject::Type::tree2].directions.push_back(Direction(-91.f, 0.f));
		data[RiverObject::Type::tree2].textureRect = sf::IntRect(1, 31, 195, 28);
		data[RiverObject::Type::tree2].speed = 70.f;

		data[RiverObject::Type::turtles1].texture = TextureID::turtles1;
		data[RiverObject::Type::turtles1].directions.push_back(Direction(91.f, 0.f));
		data[RiverObject::Type::turtles1].textureRect = sf::IntRect(125, 1, 65, 26);
		data[RiverObject::Type::turtles1].speed = 70.f;

		data[RiverObject::Type::threeTurtles1].texture = TextureID::threeTurtles1;
		data[RiverObject::Type::threeTurtles1].directions.push_back(Direction(91.f, 0.f));
		data[RiverObject::Type::threeTurtles1].textureRect = sf::IntRect(192, 1, 99, 26);
		data[RiverObject::Type::threeTurtles1].speed = 70.f;


		return data;
	}

	std::map<Vehicle::Type, VehicleData> initializeVehicleData()
	{
		std::map<Vehicle::Type, VehicleData> data;

		data[Vehicle::Type::Car].texture = TextureID::Car;
		data[Vehicle::Type::Car].directions.push_back(Direction(91.f, 0.f));
		data[Vehicle::Type::Car].textureRect = sf::IntRect( 1, 62, 35, 29);
		data[Vehicle::Type::Car].speed = 70.f;

		data[Vehicle::Type::RaceCarL].texture = TextureID::RaceCarL;
		data[Vehicle::Type::RaceCarL].directions.push_back(Direction(91.f, 0.f));
		data[Vehicle::Type::RaceCarL].textureRect = sf::IntRect(139, 100, 38, 39);
		data[Vehicle::Type::RaceCarL].speed = 90.f;

		data[Vehicle::Type::RaceCarR].texture = TextureID::RaceCarR;
		data[Vehicle::Type::RaceCarR].directions.push_back(Direction(-91.f, 0.f));
		data[Vehicle::Type::RaceCarR].textureRect = sf::IntRect(69, 100, 37, 37);
		data[Vehicle::Type::RaceCarR].speed = 90.f;

		data[Vehicle::Type::Tractor].texture = TextureID::Tractor;
		data[Vehicle::Type::Tractor].directions.push_back(Direction(-91.f, 0.f));
		data[Vehicle::Type::Tractor].textureRect = sf::IntRect(214, 62, 33, 33);
		data[Vehicle::Type::Tractor].speed = 70.f;

		data[Vehicle::Type::Truck].texture = TextureID::Truck;
		data[Vehicle::Type::Truck].directions.push_back(Direction(91.f, 0.f));
		data[Vehicle::Type::Truck].textureRect = sf::IntRect(293, 1, 61,  28);
		data[Vehicle::Type::Truck].speed = 70.f;

		return data;
	}
}