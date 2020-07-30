#include "Character.hpp"
#include "Camera/CameraComponent.hpp"
#include "Components/MovementComponent.hpp"

namespace fb
{
	ACharacter::ACharacter(World& world)
		:AActor{world},
		movement_{AddComponent<MovementComponent>()},
		camera_{AddComponent<CameraComponent>()}
	{
		SetRootComponent(&camera_);
	}
}
