#include "Character.hpp"
#include "Ball.hpp"
#include "Projectile.hpp"
#include "World.hpp"
#include "Camera/CameraComponent.hpp"
#include "Components/InputComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/SphereComponent.hpp"
#include "Components/MeshComponent.hpp"
#include "Components/SpotLightComponent.hpp"

namespace fb
{
	ACharacter::ACharacter(World& world)
		:AActor{world},
		camera_{*AddComponent<CameraComponent>()},
		collision_{*AddComponent<SphereComponent>()},
		movement_{*AddComponent<MovementComponent>()},
		floor_{*AddComponent<MeshComponent>()}
	{
		SetRootComponent(&camera_);
		camera_.SetVFov(70_deg);
		
		collision_.AttachTo(&camera_, AttachRule::kKeepRelative);
		collision_.SetUnscaledRadius(30);
		collision_.AddOnOverlap([this](SphereComponent& other)
		{
			if (dynamic_cast<ABall*>(&other.GetOwner()))
			{
				Destroy();
			}
		});

		const auto input = AddComponent<InputComponent>();
		input->BindAxis(u8"MoveForward"sv, [this](Float f) { MoveForward(f); });
		input->BindAxis(u8"MoveRight"sv, [this](Float f) { MoveRight(f); });
		input->BindAxis(u8"Turn"sv, [this](Float f) { Turn(f); });
		input->BindAction(u8"Fire"sv, true, [this]() { Fire(); });

		floor_.AttachTo(&camera_, AttachRule::kKeepRelative);
		floor_.SetMesh(u8"../Engine/Assets/Plane.omesh"sv);
		floor_.SetMaterial(u8"../Assets/Floor.omat"sv);
		floor_.SetRelTrsf({{0, 0, -100}, {}, {All{}, 100}});

		const auto spot = AddComponent<SpotLightComponent>();
		spot->AttachTo(&camera_, AttachRule::kKeepRelative);
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
		const auto proj = GetWorld().SpawnActor<AProjectile>();
		proj->SetPos(GetPos() + *GetForward() * 50);
		proj->SetRot(GetRot());
	}
}
