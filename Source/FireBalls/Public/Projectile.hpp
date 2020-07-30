#pragma once
#include "Actors/Actor.hpp"
#include "FireBalls.hpp"

namespace fb
{
	class AProjectile : public AActor
	{
	public:
		explicit AProjectile(World& world);

	protected:
		void OnUpdate(Float delta_seconds) override;

	private:
		MeshComponent& mesh_;
		SphereComponent& collision_;
	};
}
