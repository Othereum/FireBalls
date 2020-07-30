#pragma once
#include "Actors/Actor.hpp"
#include "FireBalls.hpp"

namespace fb
{
	class AFireBallsGame : public AActor
	{
	public:
		explicit AFireBallsGame(World& world);
		void OnBallDestroy();

	protected:
		void OnBeginPlay() override;
		void OnUpdate(Float delta_seconds) override;

	private:
		void StartGame();
		void CleanGame();
		
		WeakPtr<ACharacter> character_;
		TimePoint start_;
		int num_balls_ = 0;
	};
}
