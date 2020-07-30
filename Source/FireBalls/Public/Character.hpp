#pragma once
#include "Actors/Actor.hpp"
#include "FireBalls.hpp"

namespace fb
{
	class ACharacter : public AActor
	{
	public:
		explicit ACharacter(World& world);

	private:
		MovementComponent& movement_;
		CameraComponent& camera_;
	};
}
