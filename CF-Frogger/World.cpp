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
		_worldBounds(0.f, 0.f, _worldView.getSize().x, 2000.f),
		_spawnPosition(_worldView.getSize().x / 2.f, _worldBounds.height - (_worldView.getSize().y / 2)),
		_scrollSpeed(-50.0f),
		_queue(),
		_player(nullptr)
	{
		buildScene();


		//sets teh view to the bottom since we will scroll upwards
		_worldView.setCenter(_spawnPosition);

	}


	World::~World()
	{
	}

	void World::update(sf::Time deltaTime)
	{
		//_worldView.zoom(1.00001); //goes OUT slowly
		//_worldView.rotate(0.001); //spins!

		//background
		//_worldView.move(0.f, _scrollSpeed * deltaTime.asSeconds()); // moves the view which moves the background moves and not the planes
		//_player->setVelocity(0.f, 0.f);

		//destroyEnemiesOutsideView(); // sets hp = 0 if outside of view

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
		}

		spawnEnemies();*/
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
		while (!_enemySpawnPoints.empty() && (_enemySpawnPoints.back().y > getBattlefieldBounds().top))
		{
			auto spawn = _enemySpawnPoints.back();
			std::unique_ptr<Plane> enemy(new Plane(spawn.type));
			enemy->setPosition(spawn.x, spawn.y);
			enemy->setRotation(180);
			_sceneLayers[Ground]->attatchChild(std::move(enemy));
			_enemySpawnPoints.pop_back();
		}
	}

	void World::addEnemies()
	{
		// add enemy spawn points
		addEnemy(Plane::Type::Raptor, -250, 900);
		addEnemy(Plane::Type::Raptor, 300, 1800);
		addEnemy(Plane::Type::Raptor, 400, 600);
		addEnemy(Plane::Type::Raptor, 150, 1200);

		addEnemy(Plane::Type::Raptor, -150, 700);
		addEnemy(Plane::Type::Raptor, 250, 400);
		addEnemy(Plane::Type::Raptor, -350, 1500);
		addEnemy(Plane::Type::Raptor, 250, 1000);

		/*addEnemy(Plane::Type::Avenger, -450, 400);
		addEnemy(Plane::Type::Avenger, 250, 800);
		addEnemy(Plane::Type::Avenger, 350, 200);
		addEnemy(Plane::Type::Avenger, -250, 900);*/

		std::sort(_enemySpawnPoints.begin(), _enemySpawnPoints.end(), [](SpawnPoint lhs, SpawnPoint rhs) {return lhs.y < rhs.y;	});
	}

	void World::addEnemy(Plane::Type type, float relX, float relY)
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
		texture.setRepeated(true);

		std::unique_ptr<SpriteNode> _background(new SpriteNode(texture, textureRect));
		_background->setPosition(_worldBounds.left, _worldBounds.top);
		_sceneLayers[Background]->attatchChild(std::move(_background));

		// particle system
		//std::unique_ptr<ParticleNode> smokeNode(new ParticleNode(Particle::Type::smoke));
		//_sceneLayers[Air]->attatchChild(std::move(smokeNode));

		//
		//std::unique_ptr<ParticleNode> fireNode(new ParticleNode(Particle::Type::propellant));
		//_sceneLayers[Air]->attatchChild(std::move(fireNode));

		// Aircraft
		/*std::unique_ptr<Plane> plane(new Plane(Plane::Type::Eagle));
		_playerAircraft = plane.get();
		_playerAircraft->setPosition(_spawnPosition);
		_playerAircraft->setVelocity(40.f, _scrollSpeed);
		_sceneLayers[Air]->attatchChild(std::move(plane));

		sf::Texture& texture2 = TextureHolder::getInstance().get(TextureID::CloudTransparent);
		texture2.setRepeated(true);*/

		/*std::unique_ptr<SpriteNode> _background2(new SpriteNode(texture2, textureRect));
		_background2->setPosition(_worldBounds.left, _worldBounds.top);
		_sceneLayers[Air]->attatchChild(std::move(_background2));


		addEnemies();*/
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
				auto& player = static_cast<Plane&>(*pair.first);
				auto& enemy = static_cast<Plane&>(*pair.second);

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