#pragma once
namespace GEX 
{
	namespace Category
	{
		enum type {
			none = 0,		// 0000 0000
			player = 1 << 0,
			sceneGroundLayer = 1 << 1,	// 0000 0001
			playerCharacter = 1 << 2,	// 0000 0010
			enemy = 1 << 3,	// 0000 0100
			SoundEffect = 1 << 4,
			ParticleSystem = 1 << 5		// 1000 0000

		};
	}
}