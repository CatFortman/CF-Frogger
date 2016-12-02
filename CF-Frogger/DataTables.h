/**
@file
@author  Cat Fortman
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#pragma once
#include "ResourceIdentifiers.h"
#include "Plane.h"
#include "Partcile.h"
#include "Vehicle.h"
#include "RiverObject.h"

#include <map>
#include <vector>

namespace GEX
{
	struct Direction
	{
		Direction(float a, float d);
		float angle;
		float distance;
	};

	struct FrogData
	{
		int						hitPoints;
		TextureID				texture;
		std::vector<Direction>  directions; // vector describes path of Frog
		sf::IntRect				textureRect;
	};

	struct ParticleData
	{
		sf::Color								color;
		sf::Time								lifetime;
	};

	struct VehicleData
	{
		TextureID				texture;
		std::vector<Direction>  directions; // vector describes path of Vehicle
		sf::IntRect				textureRect;
		float					speed;
	};

	struct RiverObjectData
	{
		TextureID				texture;
		std::vector<Direction>  directions; // vector describes path of river object
		sf::IntRect				textureRect;
		float					speed;
	};

	std::map<Frog::Type, FrogData>					initializeFrogData();
	std::map<Particle::Type, ParticleData>			initializeParticleData();
	std::map<Vehicle::Type, VehicleData>			initializeVehicleData();
	std::map<RiverObject::Type, RiverObjectData>    initializeRiverObjectData();
}
