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

	struct CatData
	{
		int						hitPoints;
		float					speed;
		TextureID				texture;
		std::vector<Direction>  directions; // vector describes path of plyer
		sf::IntRect				textureRect;
	};

	
	struct ParticleData
	{
		sf::Color								color;
		sf::Time								lifetime;
	};

	std::map<Cat::Type, CatData>					initializeCatData();
	std::map<Particle::Type, ParticleData>			initializeParticleData();
}
