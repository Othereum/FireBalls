#pragma once
#include "Actors/Actor.hpp"
#include "FireBalls.hpp"

namespace fb
{
	class AFireBallsGame : public AActor
	{
	public:
		DELETE_CPMV(AFireBallsGame);
		
		explicit AFireBallsGame(World& world);
		~AFireBallsGame();
		
		void OnBallKilled();

	protected:
		void OnBeginPlay() override;
		void OnUpdate(Float delta_seconds) override;

	private:
		void StartGame();
		void CleanGame();
		void PrintScore() const;
		
		WeakPtr<ACharacter> character_;
		TimePoint start_;
		int num_balls_ = 0;
		int num_kills_ = 0;
	};
}
