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
#include "RiverObject.h"
#include "TextureHolder.h"
#include "SpriteNode.h"
#include "ParticleNode.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <iostream>

namespace GEX
{
	bool matchesCategories(SceneNode::pair& colliders, Category::type type1, Category::type type2)
	{
		unsigned int category1 = colliders.first->getCategory();
		unsigned int category2 = colliders.second->getCategory();


		if (type1 & category1 && type2 & category2)
		{
			//std::swap(colliders.first, colliders.second);
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
		_spawnPosition(_worldView.getSize().x / 2.f, _worldBounds.height - 20),
		_vehicleSpawnTimer(),
		_riverSpawnTimer(),
		_queue(),
		_player(nullptr),
		_frogLife1(new SpriteNode(texture2, textureRect2)),
		_frogLife2(new SpriteNode(texture2, textureRect2)),
		_frogLife3(new SpriteNode(texture2, textureRect2))
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

		destroyEnemiesOutsideView();
		// handle collsions
		handleCollisions();

		// remove all destroyed enemies
		_sceneGraph.removeWrecks();

		spawnEnemies();
		//movement
		adaptPlayerPostition();

		_sceneGraph.update(deltaTime, getCommandQueue());
		std::cout << _player->getPosition().y << std::endl;
	}


	void World::adaptPlayerPostition()
	{
		// Keep player's position inside the screen bounds, 
		// at least borderDistance units from the border

		sf::FloatRect viewBounds(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
		const float borderDistance = 15.f;

		sf::Vector2f position = _player->getPosition();
		position.x = std::max(position.x, viewBounds.left + borderDistance);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
		position.y = std::max(position.y, viewBounds.top + borderDistance);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
		_player->setPosition(position);

		if (_player->isRespawing())
		{
			respawnPlayer();
			_player->setIsRespawning(false);
		}

		// set velocity back to zero when not on a log or turtle
		if (_player->getPosition().y >= 340)
		{
			_player->setVelocity(0, 0);
		}
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
		auto spawnV = _vehicleSpawnPoints.back();	// get's the spawn point and vehicle from vector
		auto spawnVPos = spawnV;	// keeps the spawn
		std::unique_ptr<Vehicle> temp(new Vehicle(spawnV.type)); // creates the vehicle with spawn position

		// if it has been five seconds or the vehicle is not on the map then add it to the map 
		if ((_vehicleSpawnTimer.getElapsedTime() >= sf::seconds(1)) || (!getBattlefieldBounds().intersects(temp->getBoundingRect())))
		{
			//_vehicles.push_back(temp.get());

			temp->setPosition(spawnV.x, spawnV.y);
			_sceneLayers[Ground]->attatchChild(std::move(temp));
			_vehicleSpawnPoints.pop_back();
			_vehicleSpawnPoints.push_front(spawnVPos);

			_vehicleSpawnTimer.restart();
		}

		auto spawnR = _riverSpawnPoints.back();	// get's the spawn point and river from vector
		auto spawnRPos = spawnR;	// keeps the spawn
		std::unique_ptr<RiverObject> tempR(new RiverObject(spawnR.type)); // creates the river object with spawn position

																 // if it has been five seconds or the vehicle is not on the map then add it to the map 
		if ((_riverSpawnTimer.getElapsedTime() >= sf::seconds(1)) || (!getBattlefieldBounds().intersects(tempR->getBoundingRect())))
		{
			//_vehicles.push_back(temp.get());

			tempR->setPosition(spawnR.x, spawnR.y);
			_sceneLayers[Ground]->attatchChild(std::move(tempR));
			_riverSpawnPoints.pop_back();
			_riverSpawnPoints.push_front(spawnRPos);

			_riverSpawnTimer.restart();
		}
	}

	void World::addEnemies()
	{
		// add enemy spawn points
		addEnemy(Vehicle::Type::Car, 250, 120);
		addEnemy(Vehicle::Type::RaceCarL, 250, 40);
		addEnemy(Vehicle::Type::RaceCarR, -235, 160);
		addEnemy(Vehicle::Type::Tractor, -235, 80);
		addEnemy(Vehicle::Type::Truck, 250, 200);

		addEnemy(RiverObject::Type::tree1, -235, 360);
		addEnemy(RiverObject::Type::tree1, -235, 320);
		addEnemy(RiverObject::Type::tree2, -235, 440);
		addEnemy(RiverObject::Type::threeTurtles1, 235, 280);
		addEnemy(RiverObject::Type::turtles1, 235, 400);

		std::sort(_vehicleSpawnPoints.begin(), _vehicleSpawnPoints.end(), [](SpawnPointVehicle lhs, SpawnPointVehicle rhs) {return lhs.y < rhs.y;	});
		std::sort(_riverSpawnPoints.begin(), _riverSpawnPoints.end(), [](SpawnPointRiverObject lhs, SpawnPointRiverObject rhs) {return lhs.y < rhs.y;	});
	}

	void World::addEnemy(Vehicle::Type type, float relX, float relY)
	{
		addEnemy(SpawnPointVehicle(type, relX, relY));
	}

	void World::addEnemy(RiverObject::Type type, float relX, float relY)
	{
		addEnemy(SpawnPointRiverObject(type, relX, relY));
	}

	void World::addEnemy(SpawnPointVehicle point)
	{
		point.x = _spawnPosition.x + point.x;
		point.y = _spawnPosition.y - point.y;
		_vehicleSpawnPoints.push_back(point);
	}

	void World::addEnemy(SpawnPointRiverObject point)
	{
		point.x = _spawnPosition.x + point.x;
		point.y = _spawnPosition.y - point.y;
		_riverSpawnPoints.push_back(point);
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

		// Frog lives

		std::unique_ptr<SpriteNode> frogLife1(new SpriteNode(texture2, textureRect2));
		_frogLife1 = frogLife1.get();
		frogLife1->setPosition(430, 10);
		_sceneLayers[Background]->attatchChild(std::move(frogLife1));


		std::unique_ptr<SpriteNode> frogLife2(new SpriteNode(texture2, textureRect2));
		_frogLife2 = frogLife2.get();
		frogLife2->setPosition(390, 10);
		_sceneLayers[Background]->attatchChild(std::move(frogLife2));

		std::unique_ptr<SpriteNode> frogLife3(new SpriteNode(texture2, textureRect2));
		_frogLife3 = frogLife3.get();
		frogLife3->setPosition(350, 10);
		_sceneLayers[Background]->attatchChild(std::move(frogLife3));

		// add the enemies
		addEnemies();

		// Idle
		std::unique_ptr<Frog> Frog(new Frog(Frog::Type::Idle));
		_player = Frog.get();
		_player->setPosition(_spawnPosition);
		_sceneLayers[Ground]->attatchChild(std::move(Frog));
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
		if (_player->getPosition().y < 340)
		{
			if (collisionPairs.empty())
			{
				// collision: Frogger is destroyed
				if (_player->isDying() == false)
				{
					_player->setType(Frog::Type::Die1);
					_player->setIsDying(true);
				}
			}
			else
			{
				for (SceneNode::pair pair : collisionPairs)
				{
					if (matchesCategories(pair, Category::playerCharacter, Category::turtles) || matchesCategories(pair, Category::playerCharacter, Category::logs))
					{
						// safe downcasts
						auto& player = static_cast<Frog&>(*pair.first);
						auto& enemy = static_cast<RiverObject&>(*pair.second);

						// collision: Frogger is destroyed
						player.setVelocity(enemy.getVelocity().x, 0.f);
					}
				}
			}
		}

		// for each scenenode pair
		for (SceneNode::pair pair : collisionPairs)
		{
			if (matchesCategories(pair, Category::playerCharacter, Category::vehicle))
			{
				// safe downcasts
				auto& player = static_cast<Frog&>(*pair.first);
				auto& enemy = static_cast<Vehicle&>(*pair.second);

				// collision: Frogger is destroyed
				if (player.isDying() == false)
				{
					player.setType(Frog::Type::Die1);
					player.setIsDying(true);
				}
			}
		}
	}

	void World::respawnPlayer()
	{
		_player->setPosition(_spawnPosition);
	}

	void World::destroyEnemiesOutsideView()
	{
		Command command;
		command.category = Category::vehicle | Category::logs | Category::turtles;
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