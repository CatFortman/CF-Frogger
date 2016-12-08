#include "PlayerControl.h"
#include "Plane.h"
#include "Category.h"

namespace GEX 
{
	struct FrogMover {
	
		FrogMover(float vx, float vy, float degrees) : pixels(vx, vy), rotation(degrees) {}
		void operator() (Frog& Frog, sf::Time) const {
			Frog.movePlayer(pixels);
			Frog.setRotation(rotation);
			Frog.isJumping(true);
		}

		float rotation;
		sf::Vector2f pixels;
	};

	PlayerControl::PlayerControl() :
		_missionStatus(MissionStatus::Active)
	{
		initalizeKeyBindings();
		initalizeActionBindings();
	}

	void PlayerControl::handleEvent(const sf::Event& events, CommandQueue & commands)
	{
		if (events.type == sf::Event::KeyPressed)
		{
			// check if key is bound to action
			// and that its not handled as a real event
			auto found = _keyBindings.find(events.key.code);
			if (found != _keyBindings.end() && isEventAction(found->second))
			{
				commands.push(_actionBindings[found->second]);
			}
		}
	}

	void PlayerControl::handleRealTimeInput(CommandQueue& commands)
	{
		for (auto pair : _keyBindings)
		{
			if (sf::Keyboard::isKeyPressed(pair.first) && !isEventAction(pair.second))
				commands.push(_actionBindings[pair.second]);
		}
	}

	bool PlayerControl::isEventAction(Action action)
	{
		switch (action)
		{
		case Action::moveDown:
		case Action::moveLeft:
		case Action::moveRight:
		case Action::moveUp:
			return true;
		default:
			break;
		}
		return false;
	}

	void PlayerControl::initalizeKeyBindings()
	{
		_keyBindings[sf::Keyboard::A] = Action::moveLeft;
		_keyBindings[sf::Keyboard::D] = Action::moveRight;
		_keyBindings[sf::Keyboard::W] = Action::moveUp;
		_keyBindings[sf::Keyboard::S] = Action::moveDown;
	}

	void PlayerControl::initalizeActionBindings()
	{
		const float playerSpeed = 40;

		_actionBindings[Action::moveLeft].action		= derivedAction<Frog>(FrogMover(-playerSpeed, 0, -90));
		_actionBindings[Action::moveRight].action       = derivedAction<Frog>(FrogMover(playerSpeed, 0, 90));
		_actionBindings[Action::moveUp].action			= derivedAction<Frog>(FrogMover(0, -playerSpeed, 0));
		_actionBindings[Action::moveDown].action		= derivedAction<Frog>(FrogMover(0, playerSpeed, 180));
		
		for (auto& pair : _actionBindings)
			pair.second.category = Category::playerCharacter;
	}

	void PlayerControl::setMissionStatus(MissionStatus status)
	{
		_missionStatus = status;
	}

	MissionStatus PlayerControl::getMissionStatus() const
	{
		return _missionStatus;
	}
}

