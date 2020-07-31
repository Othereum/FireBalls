#pragma once
#include "Actors/Actor.hpp"
#include "FireBalls.hpp"

namespace fb
{
	class ABall : public AActor
	{
	public:
		ABall(World& world, AFireBallsGame& game);
		void SetTarget(WeakPtr<const AActor> target) noexcept { target_ = std::move(target); }

	protected:
		void OnUpdate(Float delta_seconds) override;
		
	private:
		AFireBallsGame& game_;
		MeshComponent& mesh_;
		SphereComponent& collision_;
		WeakPtr<const AActor> target_;
		int hp_;
	};
}
