
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
		_dying(false),
		_jumpTimer(0),
		_points(0),
		_deathTimer(),
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

	void Frog::adjustFrogLives()
	{
		//_frogLife1->isMarkedForRemoval();
		//		_frogLife1->destroy();
	}

	void Frog::playDeathAnimation()
	{
		if (_type == Frog::Type::Die1)
		{
			_deathTimer.restart();
			_type = Frog::Type::Die2;
			_sprite.setTexture(TextureHolder::getInstance().get(table.at(Frog::Type::Die1).texture));
			_sprite.setTextureRect(table.at(Frog::Type::Die1).textureRect);
		}
		if ((_type == Frog::Type::Die2) && (_deathTimer.getElapsedTime() >= sf::milliseconds(500)))
		{
			_deathTimer.restart();
			_type = Frog::Type::Die3;
			_sprite.setTexture(TextureHolder::getInstance().get(table.at(Frog::Type::Die2).texture));
			_sprite.setTextureRect(table.at(Frog::Type::Die2).textureRect);
		}
		if ((_type == Frog::Type::Die3) && (_deathTimer.getElapsedTime() >= sf::milliseconds(500)))
		{
			_deathTimer.restart();
			_type = Frog::Type::Idle;
			_sprite.setTexture(TextureHolder::getInstance().get(table.at(Frog::Type::Die3).texture));
			_sprite.setTextureRect(table.at(Frog::Type::Die3).textureRect);
		}
		if ((_type == Frog::Type::Idle) && (_deathTimer.getElapsedTime() >= sf::milliseconds(500)))
		{
			_deathTimer.restart();
			_sprite.setTexture(TextureHolder::getInstance().get(table.at(Frog::Type::Idle).texture));
			_sprite.setTextureRect(table.at(Frog::Type::Idle).textureRect);
			setIsDying(false);
			setIsRespawning(true);
		}
	}

	void Frog::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		// check if Frogger died
		
		if (!isDying() && !isRespawing())
		{
			checkIfJumping();
			_jumpTimer++;
			movementUpdate(dt);
			Entity::updateCurrent(dt, commands);
		}
		else
		{
			playDeathAnimation();
		}
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

	void Frog::setIsDying(bool dying)
	{
		_dying = dying;
	}

	bool Frog::isDying()
	{
		return _dying;
	}

	void Frog::setIsRespawning(bool respawning)
	{
		_respawning = respawning;
	}

	bool Frog::isRespawing()
	{
		return _respawning;
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

	void Frog::setType(Frog::Type type)
	{
		_type = type;
	}
}