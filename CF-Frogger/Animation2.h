/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION

*/
#pragma once



#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include <vector>

namespace GEX
{
	//
	// An animaiton is a collection of frames. 
	// 

	using Frame = sf::IntRect;

	class Animation2
	{
	public:
									Animation2(bool repeat = true);
									~Animation2();

		void						addFrame(const Frame& frame);
        void                        addFrameSet(const std::vector<Frame>);
		void						setDurationAsSeconds(float d);
		void						start();

		int							getNumberOfFrames() const;
		Frame						getFrameByNumber(int n) const;
		Frame						getCurrentFrame() const;
		Frame						update(sf::Time dt);


	private:
		std::vector<Frame>			_frames;
		std::size_t					_currentFrame;
		sf::Time					_elapsedTime;
		sf::Time					_duration;
		//sf::Time					_timePerFrame;
		bool						_repeat;

	};
}
