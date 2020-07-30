#include "Character.hpp"
#include "World.hpp"
#include "Camera/CameraComponent.hpp"
#include "Components/InputComponent.hpp"
#include "Components/MovementComponent.hpp"

namespace fb
{
	ACharacter::ACharacter(World& world)
		:AActor{world},
		movement_{AddComponent<MovementComponent>()},
		camera_{AddComponent<CameraComponent>()}
	{
		SetRootComponent(&camera_);

		auto& input = AddComponent<InputComponent>();
		input.BindAxis(u8"MoveForward"sv, [this](Float f) { MoveForward(f); });
		input.BindAxis(u8"MoveRight"sv, [this](Float f) { MoveRight(f); });
		input.BindAxis(u8"Turn"sv, [this](Float f) { Turn(f); });
		input.BindAction(u8"Fire"sv, true, [this]() { Fire(); });
	}

	void ACharacter::MoveForward(Float f) const noexcept
	{
		if (IsNearlyZero(f)) return;
		movement_.AddMovInput(*GetForward() * f);
	}

	void ACharacter::MoveRight(Float f) const noexcept
	{
		if (IsNearlyZero(f)) return;
		movement_.AddMovInput(*GetRight() * f);
	}

	void ACharacter::Turn(Float f) const noexcept
	{
		const auto delta = GetWorld().GetDeltaSeconds();
		movement_.AddRotInput({UVec3::up, 360_deg * f * delta});
	}

	void ACharacter::Fire() const
	{
	}
}
