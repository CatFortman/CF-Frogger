/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION

*/

#include "Animation2.h"

#include <cassert>


namespace GEX {


	Animation2::Animation2(bool repeat) :
		_currentFrame(0),
		_elapsedTime(sf::Time::Zero),
		_duration(sf::Time::Zero),
		_repeat(repeat)
	{}


	Animation2::~Animation2()
	{}

	void Animation2::addFrame(const Frame& frame)
	{
		_frames.push_back(frame);
	}

    void Animation2::addFrameSet(const std::vector<Frame> frames)
    {
        _frames = frames;
        
    }
	void Animation2::setDurationAsSeconds(float d)
	{
		_duration = sf::seconds(d);
	}

	void Animation2::start()
	{
		assert(_frames.size() > 0);
		_currentFrame = 0;
		_elapsedTime = sf::Time::Zero;
	}

	int Animation2::getNumberOfFrames() const
	{
		return _frames.size();
	}

	Frame Animation2::getFrameByNumber(int n) const
	{
		return _frames[n];
	}

	Frame Animation2::getCurrentFrame() const
	{
		assert(_currentFrame < _frames.size());
		return _frames[_currentFrame];
	}

	Frame Animation2::update(sf::Time dt)
	{
		if (getNumberOfFrames() == 1)			// optimizaion for single frame
			return _frames[_currentFrame];

		sf::Time  timePerFrame = _duration / static_cast<float>(_frames.size());
		_elapsedTime += dt;

		while (_elapsedTime >= timePerFrame && _currentFrame < _frames.size())
		{
			++_currentFrame;
			if (_repeat)
				_currentFrame %= _frames.size();

			_elapsedTime -= timePerFrame;
		}

		if (_currentFrame >= _frames.size())
			_currentFrame = _frames.size() - 1;		// be safe

		return _frames[_currentFrame];
	}
}
