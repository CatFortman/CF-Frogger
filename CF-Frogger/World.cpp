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

	World::World(sf::RenderWindow& window, SoundPlayer& soundPlayer) :
		_window(window),
		_worldView(window.getDefaultView()),
		_sceneGraph(),
		_sceneLayers(),
		_worldBounds(0.f, 0.f, _worldView.getSize().x, 2000.f),
		_spawnPosition(_worldView.getSize().x / 2.f, _worldBounds.height - (_worldView.getSize().y / 2)),
		_scrollSpeed(-50.0f),
		_queue(),
		_player(nullptr),
		_soundPlayer(soundPlayer)
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
		_worldView.move(0.f, _scrollSpeed * deltaTime.asSeconds()); // moves the view which moves the background moves and not the planes
		_player->setVelocity(0.f, 0.f);

		updateSounds();

		// run all the commands
		while (!_queue.isEmpty())
		{
			_sceneGraph.onCommand(_queue.pop(), sf::Time::Zero);
		}

		// handle collsions
		handleCollisions();

		// remove all destroyed enemies

		// adjusting player pos
		sf::Vector2f position = _player->getPosition();
		sf::Vector2f velocity = _player->getVelocity();

		// checking OOB
		//								left side									right side
		if (position.x < _worldBounds.left + 150.f || position.x > _worldBounds.left + _worldBounds.width - 150)
		{
			velocity.x *= -1;
			_player->setVelocity(velocity);
		}

		if (position.y < 0 || position.y > _worldBounds.height)
		{
			velocity.y *= -1;
			_player->setVelocity(velocity);
		}

		//movement
		_sceneGraph.update(deltaTime, getCommandQueue());
		adaptPlayerPostition();
	}

	void World::updateSounds()
	{
		_soundPlayer.setListenerPosition(_player->getPosition());

		_soundPlayer.removeStoppedSounds();
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
		_player->setPosition(position);
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
	
	void World::buildScene()
	{
		//LAYER NODES FOR SCENE GRAPH

		for (std::size_t i = 0; i < LayerCount; i++)
		{
			Category::type category = (i == Ground) ? Category::Ground : Category::none;
			SceneNode::ptr layer(new SceneNode(category));
			_sceneLayers[i] = layer.get();
			_sceneGraph.attatchChild(std::move(layer));
		}

		//background
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::Jungle);
		sf::IntRect textureRect(0, 0, 2000, 4000);
		texture.setRepeated(true);

		std::unique_ptr<SpriteNode> _background(new SpriteNode(texture, textureRect));
		_background->setPosition(_worldBounds.left, _worldBounds.top - 2000.f);
		_sceneLayers[Background]->attatchChild(std::move(_background));

		// Zombie
		std::unique_ptr<Cat> zombie(new Cat(Cat::Type::Cat));
		_player = zombie.get();
		_player->setPosition(_spawnPosition);
		_player->setVelocity(40.f, _scrollSpeed);
		_sceneLayers[Ground]->attatchChild(std::move(zombie));

	}

	void World::handleCollisions()
	{
		// build list of all pairs of colliding scenenodes
		//std::set<SceneNode::pair> collisionPairs;
		//_sceneGraph.checkSceneCollision(_sceneGraph, collisionPairs);

		/*if (collisionPairs.size() != 0)
		{
			std::cout << collsion.pairs.size() << std::endl;
		}*/

		// for each scenenode pair
		//for (SceneNode::pair pair: collisionPairs)
		//{
		//	if (matchesCategories(pair, Category::playerCharacter, Category::EnemyAircraft))
		//	{
		//		// safe downcasts
		//		auto& player = static_cast<Cat&>(*pair.first);
		//		auto& enemy = static_cast<Cat&>(*pair.second);

		//		// collision: player damage = enemy's remaining hp
		//		player.damage(enemy.getHitPoints());
		//		enemy.destroy();
		//	}

		//	if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile))
		//	{
		//		auto& enemyAircraft = static_cast<Cat&>(*pair.first);
		//		auto& projectile = static_cast<Projectile&>(*pair.second);

		//		enemyAircraft.damage(projectile.getHitPoints());
		//		projectile.destroy();
		//	}
		//}
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