#include "GameState.h"
#include "Utility.h"
#include "MusicPlayer.h"


namespace GEX
{
	GameState::GameState(StateStack& stack, Context context) :
		State(stack, context),
		_world(*context.window),
		_player(*context.player)
	{
		context.music->play(MusicID::MissionTheme);
	}

	void GameState::draw()
	{
		_world.draw();
	}

	bool GameState::update(sf::Time dt)
	{
		_world.update(dt);

		////////////////////////////////////////////
		// check if the game is over
		if (!_world.hasAlivePlayer())
		{
			_player.setMissionStatus(MissionStatus::Fail);
			requestStackPush(StateID::GameOver);
		}
		else if (_world.hasReachFinish())
		{
			_player.setMissionStatus(MissionStatus::Success);
			requestStackPush(StateID::GameOver);
		}
		///////////////////////////////////////////

		CommandQueue& commands = _world.getCommandQueue();
		_player.handleRealTimeInput(commands);

		return true;
	}

	bool GameState::handleEvent(const sf::Event& event)
	{
		// Game input handling
		CommandQueue& commands = _world.getCommandQueue();
		_player.handleEvent(event, commands);

		// Escape pressed, trigger the pause screen
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			requestStackPush(StateID::Pause);

		// G pressed, trigger the GEX screen
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
			requestStackPush(StateID::GEX);

		return true;
	}

}
