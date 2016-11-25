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

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <set>

#include "Command.h"
#include "Category.h"
#include "CommandQueue.h"

namespace GEX 
{
	class SceneNode : public sf::Transformable, public sf::Drawable 
	{

	public:
	
	typedef std::unique_ptr<SceneNode> ptr; //instead of typing out the whole unique ptr
	typedef std::pair<SceneNode*, SceneNode*> pair;
	
	public:
									SceneNode(Category::type category = Category::none);
		virtual						~SceneNode();

									SceneNode(const SceneNode&) = delete;
		SceneNode&					operator=(const SceneNode&) = delete;
		void						attatchChild(ptr);
		ptr							detachChild(const SceneNode& node);
		void						update(sf::Time dt, CommandQueue& commands);
		void						onCommand(const Command& command, sf::Time dt);
		virtual unsigned int		getCategory() const;

		sf::Vector2f				getWorldPosition() const;
		sf::Transform				getWorldTransform() const;
		virtual sf::FloatRect		getBoundingRect() const;

		void						drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

		void						checkSceneCollision(SceneNode& node, std::set<pair>& collisionPairs);
		void						checkNodeCollision(SceneNode& node, std::set<pair>& collisionPairs);

		void						removeWrecks();
		virtual bool				isMarkedForRemoval() const;
		virtual bool				isDestroyed() const;

	private:

		
		virtual void				updateCurrent(sf::Time dt, CommandQueue& commands);
		void						updateChildren(sf::Time dt, CommandQueue& commands);

		//draw methods go here
		void						draw(sf::RenderTarget& target, sf::RenderStates state)const override final;
		virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
		void						drawChildren(sf::RenderTarget& target, sf::RenderStates state) const;

	private:
		SceneNode*					_parent;
		std::vector<ptr>			_children;
		Category::type				_defaultCategory;
		static int					_objCount;
	};

	float							distance(const SceneNode& lhs, const SceneNode& rhs);
	bool							collision(const SceneNode& lhs, const SceneNode& rhs);
}

