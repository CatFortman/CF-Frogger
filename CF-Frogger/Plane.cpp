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

		_isMarkedForRemoval(false)
	{
		// set up the animation

		centerOrigin(_sprite);
		//
		// build fire and launch commands
		//
		
		//
		// build mini-HUD for aircraft
		//

		// TextureHolder::getInstance().load(TextureID::AIRFrog, "../media/Textures/Froggers.png");
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
		// normalize speed
		// needed when travelling diagonl
		sf::Vector2f velo = getVelocity();
		if (velo.x != 0.f && velo.y != 0.f)
			setVelocity(velo / std::sqrt(2.f));

		if (isDestroyed())
		{
			return;
		}

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

	bool Frog::isAllied() const
	{
		return _type == Type::Frogger;
	}

	bool Frog::isMarkedForRemoval() const
	{
		return isDestroyed();
	}
}