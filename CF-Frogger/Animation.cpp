/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#include "Animation.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace GEX
{

	Animation::Animation() :
		_sprite(),
		_frameSize(),
		_numFrames(0),
		_currentFrame(0),
		_duration(sf::Time::Zero),
		_elapsedTime(sf::Time::Zero),
		_repeat(false)
	{}

	Animation::Animation(const sf::Texture& texture) :
		_sprite(texture),
		_frameSize(),
		_numFrames(0),
		_currentFrame(0),
		_duration(sf::Time::Zero),
		_elapsedTime(sf::Time::Zero),
		_repeat(false)
	{}

	void Animation::setTexture(const sf::Texture& texture)
	{
		_sprite.setTexture(texture);
	}

	const sf::Texture* Animation::getTexture() const
	{
		return _sprite.getTexture();
	}

	void Animation::setFrameSize(sf::Vector2i frameSize)
	{
		_frameSize = frameSize;
	}

	sf::Vector2i Animation::getFrameSize() const
	{
		return _frameSize;
	}

	void Animation::setNumFrames(std::size_t numFrames)
	{
		_numFrames = numFrames;
	}

	std::size_t Animation::getNumFrames() const
	{
		return _numFrames;
	}

	void Animation::setDuration(sf::Time duration)
	{
		_duration = duration;
	}

	sf::Time Animation::getDuration() const
	{
		return _duration;
	}

	void Animation::setRepeating(bool flag)
	{
		_repeat = flag;
	}

	bool Animation::isRepeating() const
	{
		return _repeat;
	}

	void Animation::restart()
	{
		_currentFrame = 0;
	}

	bool Animation::isFinished() const
	{
		return _currentFrame >= _numFrames;
	}

	sf::FloatRect Animation::getLocalBounds() const
	{
		return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
	}

	sf::FloatRect Animation::getGlobalBounds() const
	{
		return getTransform().transformRect(getLocalBounds());
	}

	void Animation::update(sf::Time dt)
	{
		sf::Time timePerFrame = _duration / static_cast<float>(_numFrames);
		_elapsedTime += dt;

		sf::Vector2i textureBounds(_sprite.getTexture()->getSize());
		sf::IntRect textureRect = _sprite.getTextureRect();

		if (_currentFrame == 0)
			textureRect = sf::IntRect(0, 0, _frameSize.x, _frameSize.y);

		// While we have a frame to process
		while (_elapsedTime >= timePerFrame && (_currentFrame <= _numFrames || _repeat))
		{
			// Move the texture rect left
			textureRect.left += textureRect.width;

			// If we reach the end of the texture
			if (textureRect.left + textureRect.width > textureBounds.x)
			{
				// Move it down one line
				textureRect.left = 0;
				textureRect.top += textureRect.height;
			}

			// And progress to next frame
			_elapsedTime -= timePerFrame;
			if (_repeat)
			{
				_currentFrame = (_currentFrame + 1) % _numFrames;

				if (_currentFrame == 0)
					textureRect = sf::IntRect(0, 0, _frameSize.x, _frameSize.y);
			}
			else
			{
				_currentFrame++;
			}
		}

		_sprite.setTextureRect(textureRect);
	}

	void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(_sprite, states);
	}

}