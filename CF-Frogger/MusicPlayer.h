#pragma once
#include <SFML/Audio/Music.hpp>

#include <set>
#include <map>

namespace GEX
{
	enum class MusicID {
		MenuTheme,
		MissionTheme
	};
	class MusicPlayer
	{
	public:
		MusicPlayer();

		MusicPlayer(const MusicPlayer&) = delete; // non-copyable
		MusicPlayer& operator =(const MusicPlayer&) = delete;

		void play(MusicID theme);
		void stop();

		void setPaused(bool paused);
		void setVolume(float volume);

	private:
		sf::Music	_music;
		std::map<MusicID, std::string> _fileNames;
		float _volume;
	};
}
