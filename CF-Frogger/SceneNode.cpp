#include "SceneNode.h"
#include "Category.h"
#include "Utility.h"

#include <algorithm>
#include <cassert>
#include <iostream>

namespace GEX 
{
	float distance(const SceneNode& lhs, const SceneNode& rhs)
	{
		return length(lhs.getWorldPosition() - rhs.getWorldPosition());
	}

	int      SceneNode::_objCount = 0;

	SceneNode::SceneNode(Category::type cat) :
		_parent(nullptr),
		_defaultCategory(cat)
	{
		std::cout << ++_objCount << std::endl;
	}


	SceneNode::~SceneNode()
	{
		std::cout << --_objCount << std::endl;
	}

	void SceneNode::attatchChild(ptr child)
	{
		child->_parent = this;
		_children.push_back(std::move(child));
	}

	SceneNode::ptr SceneNode::detachChild(const SceneNode & node)
	{
		auto found = std::find_if(_children.begin(), _children.end(), [&](ptr& p)->bool {return p.get() == &node; });
		assert(found == _children.end()); //wasn't found
		ptr result = std::move(*found);
		result->_parent = nullptr;
		_children.erase(found);
			return result;
	}

	void SceneNode::update(sf::Time dt, CommandQueue& commands)
	{
		updateCurrent(dt, commands);
		updateChildren(dt, commands);
	}

	void SceneNode::onCommand(const Command & command, sf::Time dt)
	{
		if(command.category & getCategory())
			command.action(*this, dt);

		for (auto& child : _children)
			child->onCommand(command, dt);
	}

	unsigned int SceneNode::getCategory() const
	{
		return _defaultCategory;
	}

	void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		//overridden from elsewhere
	}

	void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
	{
		for (const ptr& child : _children)
		{
			child->update(dt, commands);
		}
	}

	void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates state) const
	{
		state.transform *= getTransform();

		drawCurrent(target, state);
		drawChildren(target, state);

		drawBoundingRect(target, state);
	}

	void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{

	}

	void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates state) const
	{
		for (const ptr& child : _children)
		{
			child->draw(target, state);
		}
	}

	sf::Vector2f SceneNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}

	sf::Transform SceneNode::getWorldTransform() const
	{
		sf::Transform transform = sf::Transform::Identity;
		for (const SceneNode* node = this; node != nullptr; node = node->_parent)
		{
			transform = node->getTransform() * transform;
		}
		return transform;
	}

	sf::FloatRect SceneNode::getBoundingRect() const
	{
		return sf::FloatRect(); // default behavior return empty rect
	}

	void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sf::FloatRect rect = getBoundingRect();

		sf::RectangleShape shape;
		shape.setPosition(sf::Vector2f(rect.left, rect.top));
		shape.setSize(sf::Vector2f(rect.width, rect.height));
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Red);
		shape.setOutlineThickness(1.f);

		target.draw(shape);
	}

	void SceneNode::checkSceneCollision(SceneNode& node, std::set<pair>& collisionPairs)
	{
		this->checkNodeCollision(node, collisionPairs);

		for (auto& child : node._children)
		{
			this->checkSceneCollision(*child, collisionPairs);
		}
	}

	void SceneNode::checkNodeCollision(SceneNode& node, std::set<pair>& collisionPairs)
	{
		if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
		{
			collisionPairs.insert(std::minmax(this, &node));
		}

		for (auto& child : _children)
		{
			child->checkNodeCollision(node, collisionPairs);
		}
	}

	bool collision(const SceneNode& lhs, const SceneNode& rhs)
	{
		return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
	}

	void SceneNode::removeWrecks()
	{
		// remove all children if requested
		auto wreckFieldBegin = std::remove_if(_children.begin(), _children.end(), 
			std::mem_fn(&SceneNode::isMarkedForRemoval));

		if (wreckFieldBegin != _children.end())
		{
			std::cout << "wrecks " << std::endl;
		}

		_children.erase(wreckFieldBegin, _children.end());
 

		// call function recursively for all remaining children
		std::for_each(_children.begin(), _children.end(), std::mem_fn(&SceneNode::removeWrecks));
	}

	bool SceneNode::isMarkedForRemoval() const
	{
		return isDestroyed();
	}

	bool SceneNode::isDestroyed() const
	{
		return false;
	}
}
