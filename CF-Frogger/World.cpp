/**
@file
@author  Cat Fortman
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#include "World.h"
#include "Plane.h"
#include "TextureHolder.h"
#include "SpriteNode.h"
#include "ParticleNode.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdlib>

namespace GEX
{
	bool matchesCategories(SceneNode::pair& colliders, Category::type type1, Category::type type2)
	{
		unsigned int category1 = colliders.first->getCategory();
		unsigned int category2 = colliders.second->getCategory();

		
		if (type1 & category1 && type2 & category2)
		{
			std::swap(colliders.first, colliders.second);
			return true;
		}
		else if (type1 & category2 && type2 & category1)
		{
			std::swap(colliders.first, colliders.second);
			return true;
		}
		else
		{
			return false;
		}
	}

	World::World(sf::RenderWindow& window) :
		_window(window),
		_worldView(window.getDefaultView()),
		_sceneGraph(),
		_sceneLayers(),
		_worldBounds(0.f, 0.f, _worldView.getSize().x, _worldView.getSize().y),
		_spawnPosition(_worldView.getSize().x / 2.f, _worldBounds.height - 20 ),
		_enemySpawnTimer(),
		_queue(),
		_player(nullptr)
	{
		buildScene();

		//sets teh view to the bottom since we will scroll upwards
		//_worldView.setCenter(_spawnPosition);

	}


	World::~World()
	{
	}

	void World::update(sf::Time deltaTime)
	{
		// run all the commands
		while (!_queue.isEmpty())
		{
			_sceneGraph.onCommand(_queue.pop(), sf::Time::Zero);
		}

		// handle collsions
		//handleCollisions();

		// remove all destroyed enemies
		//_sceneGraph.removeWrecks();

		// adjusting player pos
		//sf::Vector2f position = _player->getPosition();
		//sf::Vector2f velocity = _player->getVelocity();

		// checking OOB
		//								left side									right side
		/*if (position.x < _worldBounds.left + 150.f || position.x > _worldBounds.left + _worldBounds.width - 150)
		{
			velocity.x *= -1;
			_playerAircraft->setVelocity(velocity);
		}

		if (position.y < 0 || position.y > _worldBounds.height)
		{
			velocity.y *= -1;
			_playerAircraft->setVelocity(velocity);
		}*/;

		spawnEnemies();
		//movement
		_sceneGraph.update(deltaTime, getCommandQueue());
		//adaptPlayerPostition();
	}


	void World::adaptPlayerPostition()
	{
		// Keep player's position inside the screen bounds, 
		// at least borderDistance units from the border

		sf::FloatRect viewBounds(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
		const float borderDistance = 35.f;

		sf::Vector2f position = _player->getPosition();
		position.x = std::max(position.x, viewBounds.left + borderDistance);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
		position.y = std::max(position.y, viewBounds.top + borderDistance);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
		//_playerAircraft->setPosition(position);
	}

	void World::draw()
	{
		_window.setView(_worldView);
		_window.draw(_sceneGraph);
	}

	CommandQueue & World::getCommandQueue()
	{
		return _queue;
	}

	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
	}

	sf::FloatRect World::getBattlefieldBounds() const
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.top -= 100;
		bounds.height += 100;
		return bounds;
	}

	void World::spawnEnemies()
	{
		auto spawn = _enemySpawnPoints.back();	// get's the spawn point and vehicle from vector
		auto spawnPos = spawn;	// keeps the spawn
		std::unique_ptr<Vehicle> temp(new Vehicle(spawn.type)); // creates the vehicle with spawn position

		// if it has been five seconds or the vehicle is not on the map then add it to the map 
		if ((_enemySpawnTimer.getElapsedTime() >= sf::seconds(1)) || (!getBattlefieldBounds().intersects(temp->getBoundingRect())))
		{
			//_vehicles.push_back(temp.get());

			temp->setPosition(spawn.x, spawn.y);
			_sceneLayers[LaneNode]->attatchChild(std::move(temp));
			_enemySpawnPoints.pop_back();
			_enemySpawnPoints.push_front(spawnPos);
	
			_enemySpawnTimer.restart();
		}
	}

	void World::addEnemies()
	{
		// add enemy spawn points
		addEnemy(Vehicle::Type::Car, 250, _worldBounds.height - 480);
		addEnemy(Vehicle::Type::RaceCarL, 300, _worldBounds.height - 560);
		addEnemy(Vehicle::Type::RaceCarR, -235, _worldBounds.height - 440);
		addEnemy(Vehicle::Type::Tractor, -235, _worldBounds.height - 520);
		addEnemy(Vehicle::Type::Truck, 250, _worldBounds.height - 400);

		addEnemy(Vehicle::Type::Car, 250, _worldBounds.height - 480);
		addEnemy(Vehicle::Type::RaceCarL, 300, _worldBounds.height - 560);
		addEnemy(Vehicle::Type::RaceCarR, -235, _worldBounds.height - 440);
		addEnemy(Vehicle::Type::Tractor, -235, _worldBounds.height - 520);
		addEnemy(Vehicle::Type::Truck, 250, _worldBounds.height - 400);

		std::sort(_enemySpawnPoints.begin(), _enemySpawnPoints.end(), [](SpawnPoint lhs, SpawnPoint rhs) {return lhs.y < rhs.y;	});
	}

	void World::addEnemy(Vehicle::Type type, float relX, float relY)
	{
		addEnemy(SpawnPoint(type, relX, relY));
	}

	void World::addEnemy(SpawnPoint point)
	{
		point.x = _spawnPosition.x + point.x;
		point.y = _spawnPosition.y - point.y;
		_enemySpawnPoints.push_back(point);
	}

	void World::buildScene()
	{
		//LAYER NODES FOR SCENE GRAPH
		for (std::size_t i = 0; i < LayerCount; i++)
		{
			Category::type category = (i == Ground) ? Category::sceneGroundLayer : Category::none;
			SceneNode::ptr layer(new SceneNode(category));
			_sceneLayers[i] = layer.get();
			_sceneGraph.attatchChild(std::move(layer));
		}

		//background
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::Background);
		sf::IntRect textureRect(_worldBounds);

		std::unique_ptr<SpriteNode> _background(new SpriteNode(texture, textureRect));
		_background->setPosition(_worldBounds.left, _worldBounds.top);
		_sceneLayers[Background]->attatchChild(std::move(_background));

		// particle system
		//std::unique_ptr<ParticleNode> smokeNode(new ParticleNode(Particle::Type::smoke));
		//_sceneLayers[Air]->attatchChild(std::move(smokeNode));

		//
		//std::unique_ptr<ParticleNode> fireNode(new ParticleNode(Particle::Type::propellant));
		//_sceneLayers[Air]->attatchChild(std::move(fireNode));

		// Idle
		std::unique_ptr<Frog> Frog(new Frog(Frog::Type::Idle));
		_player = Frog.get();
		_player->setPosition(_spawnPosition);
		_sceneLayers[Ground]->attatchChild(std::move(Frog));

		// Frog lives
		sf::Texture& texture2 = TextureHolder::getInstance().get(TextureID::FrogLives);
		sf::IntRect textureRect2(395,100,39,40);

		std::unique_ptr<SpriteNode> _frogLife1(new SpriteNode(texture2, textureRect2));
		_frogLife1->setPosition(_worldView.getSize().x - 50, _worldBounds.height - 590);
		_sceneLayers[Background]->attatchChild(std::move(_frogLife1));

		std::unique_ptr<SpriteNode> _frogLife2(new SpriteNode(texture2, textureRect2));
		_frogLife2->setPosition(_worldView.getSize().x - 90, _worldBounds.height - 590);
		_sceneLayers[Background]->attatchChild(std::move(_frogLife2));

		std::unique_ptr<SpriteNode> _frogLife3(new SpriteNode(texture2, textureRect2));
		_frogLife3->setPosition(_worldView.getSize().x - 130, _worldBounds.height - 590);
		_sceneLayers[Background]->attatchChild(std::move(_frogLife3));

		// add the enemies
		addEnemies();
	}

	void World::handleCollisions()
	{
		// build list of all pairs of colliding scenenodes
		std::set<SceneNode::pair> collisionPairs;
		_sceneGraph.checkSceneCollision(_sceneGraph, collisionPairs);

		/*if (collisionPairs.size() != 0)
		{
			std::cout << collsion.pairs.size() << std::endl;
		}*/

		// for each scenenode pair
		for (SceneNode::pair pair: collisionPairs)
		{
			if (matchesCategories(pair, Category::none, Category::none))
			{
				// safe downcasts
				auto& player = static_cast<Frog&>(*pair.first);
				auto& enemy = static_cast<Frog&>(*pair.second);

				// collision: player damage = enemy's remaining hp
				player.damage(enemy.getHitPoints());
				enemy.destroy();
			}
		}
	}

	void World::destroyEnemiesOutsideView()
	{
		Command command;
		command.category = Category::none | Category::none;
		command.action = derivedAction<Entity>([this](Entity& e, sf::Time)
		{
			if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
				e.destroy();
		});
		_queue.push(command);
	}

	bool World::hasAlivePlayer() const
	{
		return !_player->isMarkedForRemoval();
	}

	bool World::hasReachFinish() const
	{
		return !_worldBounds.contains(_player->getPosition());
	}
}