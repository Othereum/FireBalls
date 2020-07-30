#pragma once
#include "Actors/Actor.hpp"
#include "FireBalls.hpp"

namespace fb
{
	class ABall : public AActor
	{
	public:
		explicit ABall(World& world);

	private:
		MeshComponent& mesh_;
	};
}
