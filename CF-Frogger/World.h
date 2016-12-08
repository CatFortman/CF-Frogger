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

#include "SFML\graphics.hpp"
#include "SceneNode.h"
#include "CommandQueue.h"
#include "Plane.h"
#include "Vehicle.h"
#include "RiverObject.h"
#include "SpriteNode.h"
#include "TextureHolder.h"

#include <vector>
#include <array>

namespace GEX 
{
	bool matchesCategories(SceneNode::pair& colliders, Category::type type1, Category::type type2);

	class World
	{
	public:

		explicit		World(sf::RenderWindow& window);
						~World();
		World&			operator=(const World&) = delete;

		void			update(sf::Time deltaTime);

		void			draw();
		Frog*			getPlayer() { return _player; }
		CommandQueue&	getCommandQueue();

		bool			hasAlivePlayer() const;
		bool			hasReachFinish() const;
		
	private:

		struct SpawnPointVehicle
		{
			SpawnPointVehicle(Vehicle::Type type, float _x, float _y) :
				type(type),
				x(_x),
				y(_y) {}
			Vehicle::Type type;
			float		x;
			float		y;
		};


		struct SpawnPointRiverObject
		{
			SpawnPointRiverObject(RiverObject::Type type, float _x, float _y) :
				type(type),
				x(_x),
				y(_y) {}
			RiverObject::Type type;
			float		x;
			float		y;
		};

	private:

		void			buildScene();

		sf::FloatRect	getViewBounds() const;
		sf::FloatRect	getBattlefieldBounds() const;

		void			adaptPlayerPostition();

		void			respawnPlayer();

		void			spawnEnemies();
		void			addEnemies();
		void			addEnemy(Vehicle::Type type, float relX, float relY);
		void			addEnemy(RiverObject::Type type, float relX, float relY);
		void			addEnemy(SpawnPointVehicle point);
		void			addEnemy(SpawnPointRiverObject point);

		void			handleCollisions();
		void			destroyEnemiesOutsideView();

	private:

		enum _Layers
		{
			Background,
			Ground,
			Road,
			RiverNode,
			LayerCount
		};

		sf::RenderWindow&					_window;
		sf::View							_worldView;
		SceneNode							_sceneGraph;

		std::array<SceneNode*, LayerCount>	_sceneLayers;
		CommandQueue						_queue;
		sf::FloatRect						_worldBounds;
		sf::Vector2f						_spawnPosition;
		float								_scrollSpeed;
		Frog*								_player;

		sf::Clock							_vehicleSpawnTimer;
		sf::Clock							_riverSpawnTimer;

		sf::Texture&						texture2 = TextureHolder::getInstance().get(TextureID::FrogLives);
		sf::IntRect							textureRect2 = sf::IntRect(395, 100, 39, 40);

		SpriteNode*			_frogLife1;
		SpriteNode*			_frogLife2;
		SpriteNode*			_frogLife3;

		std::deque<SpawnPointVehicle>		_vehicleSpawnPoints;
		std::deque<SpawnPointRiverObject>	_riverSpawnPoints;
		std::vector<Vehicle*>				_vehicles;
		std::vector<Vehicle*>				_activeEnemies;
	};
}
