#pragma once
#include "SFML\graphics.hpp"

namespace GEX
{
	class Animation : public sf::Drawable, public sf::Transformable
	{
	public:
		explicit Animation(const sf::Texture& texture);
		Animation();

		void restart();
		bool isFinished() const;

		void setFrameSize(sf::Vector2i size);
		sf::Vector2i getFrameSize() const;

		void Animation::setTexture(const sf::Texture& texture);
		const sf::Texture* Animation::getTexture() const;

		void setRepeating(bool flag);
		bool isRepeating() const;

		void setNumFrames(std::size_t frames);
		std::size_t  getNumFrames() const;

		void setDuration(sf::Time dt);
		sf::Time getDuration() const;

		sf::FloatRect	getLocalBounds() const;
		sf::FloatRect	getGlobalBounds() const;

		void	update(sf::Time delta);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Sprite		_sprite;
		sf::Vector2i	_frameSize;
		std::size_t		_numFrames;
		std::size_t		_currentFrame;
		sf::Time		_duration;
		sf::Time		_elapsedTime;
		bool			_repeat;

	};
}
