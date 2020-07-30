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
		void MoveForward(Float f) const noexcept;
		void MoveRight(Float f) const noexcept;
		void Turn(Float f) const noexcept;
		void Fire() const;
		
		MovementComponent& movement_;
		CameraComponent& camera_;
	};
}
