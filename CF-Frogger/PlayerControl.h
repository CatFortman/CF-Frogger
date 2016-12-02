#pragma once
#include "SFML\graphics.hpp"
#include "CommandQueue.h"
#include <map>

namespace GEX
{
	enum class MissionStatus {
		Active,
		Success,
		Fail
	};

	class PlayerControl
	{
		enum class Action {
			moveLeft,
			moveRight,
			moveUp,
			moveDown
		};

	public:
		PlayerControl();

		void			handleEvent(const sf::Event& events, CommandQueue& commands);
		void			handleRealTimeInput(CommandQueue& commands);

		void			setMissionStatus(MissionStatus status);
		MissionStatus	getMissionStatus() const;

	private:
		void			initalizeKeyBindings();
		void			initalizeActionBindings();
		bool			isEventAction(Action action);

	private:
		std::map<sf::Keyboard::Key, Action> _keyBindings;
		std::map<Action, Command>			_actionBindings;
		MissionStatus						_missionStatus;
	};
}