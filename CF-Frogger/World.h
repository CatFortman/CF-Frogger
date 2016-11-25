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
		Plane*			getPlayer() { return _player; }
		CommandQueue&	getCommandQueue();

		bool			hasAlivePlayer() const;
		bool			hasReachFinish() const;
		
	private:

		struct SpawnPoint
		{
			SpawnPoint(Plane::Type type, float _x, float _y) :
				type(type),
				x(_x),
				y(_y) {}
			Plane::Type type;
			float		x;
			float		y;
		};

	private:

		void			buildScene();

		sf::FloatRect	getViewBounds() const;
		sf::FloatRect	getBattlefieldBounds() const;

		void			adaptPlayerPostition();

		void			spawnEnemies();
		void			addEnemies();
		void			addEnemy(Plane::Type type, float relX, float relY);
		void			addEnemy(SpawnPoint point);

		void			handleCollisions();
		void			destroyEnemiesOutsideView();

	private:

		enum _Layers
		{
			Background,
			Ground,
			Road,
			River,
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
		Plane*								_player;
		std::vector<SpawnPoint>				_enemySpawnPoints;

		std::vector<Plane*>					_activeEnemies;
	};
}
