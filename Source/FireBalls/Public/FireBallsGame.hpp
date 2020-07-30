#pragma once
#include "Actors/Actor.hpp"
#include "FireBalls.hpp"

namespace fb
{
	class AFireBallsGame : public AActor
	{
	public:
		explicit AFireBallsGame(World& world);

	private:
		void SpawnBall();
		
		ACharacter& character_;
		DyArr<std::reference_wrapper<ABall>> balls_;
	};
}
