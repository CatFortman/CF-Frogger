#pragma once
namespace GEX 
{
	namespace Category
	{
		enum type {
			none = 0,		// 0000 0000
			ParticleSystem = 1 << 0,		// 1000 0000
			Ground = 1 << 1,
			SoundEffect = 1 << 2,
			playerCharacter = 1 << 3

		};
	}
}