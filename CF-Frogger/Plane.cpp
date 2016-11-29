#include "Plane.h"
#include "TextureHolder.h"
#include "ResourceIdentifiers.h"
#include "TextNode.h"
#include "Utility.h"
#include "DataTables.h"

#include <cassert>
namespace GEX 
{
	const std::map<Frog::Type, FrogData> table = initializeFrogData();

	TextureID toTextureID(Frog::Type type)
	{
		return TextureID::Frog;
	}

	Frog::Frog(Type type) :
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect),
		_directionIndex(0),
		_jumping(false),
		_jumpTimer(0),
		_isMarkedForRemoval(false)
	{
		// set up the animation
		centerOrigin(_sprite);

		// TextureHolder::getInstance().load(TextureID::AIRFrog, "../media/Textures/Idles.png");
		sf::FloatRect bounds = _sprite.getLocalBounds();
		_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

		std::unique_ptr<TextNode> healthDisplay(new TextNode(std::to_string(getHitPoints()) + "HP"));
		_healthDisplay = healthDisplay.get();
		healthDisplay->setPosition(0.f, 50.f);
		attatchChild(std::move(healthDisplay));
	}

	unsigned int Frog::getCategory() const
	{
		return Category::playerCharacter;
	}

	sf::FloatRect Frog::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void Frog::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Frog::movementUpdate(sf::Time dt)
	{
	}

	void Frog::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		// check if Idle died
		if (isDestroyed())
		{
			return;
		}

		checkIfJumping();
		_jumpTimer++;
		movementUpdate(dt);
		Entity::updateCurrent(dt, commands);

		updateTexts();
	}

	void Frog::updateTexts()
	{
		/*_healthDisplay->setText(std::to_string(getHitPoints()) + "HP");
		_healthDisplay->setPosition(0.f, 50.f);
		_healthDisplay->setRotation(-getRotation());*/
	}

	bool Frog::isMarkedForRemoval() const
	{
		return isDestroyed();
	}

	void Frog::isJumping(bool jumping)
	{
		_jumping = jumping;
	}

	void Frog::checkIfJumping()
	{
		if (_jumpTimer == 15)
		{
			_jumpTimer = 0;
			_sprite.setTexture(TextureHolder::getInstance().get(table.at(Frog::Type::Idle).texture));
			_sprite.setTextureRect(table.at(Frog::Type::Idle).textureRect);
		}
		if (_jumping)
		{
			_sprite.setTexture(TextureHolder::getInstance().get(table.at(Frog::Type::Jumping).texture));
			_sprite.setTextureRect(table.at(Frog::Type::Jumping).textureRect);
			isJumping(false);
		}
	}
}