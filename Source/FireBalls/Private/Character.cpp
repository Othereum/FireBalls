#include "Character.hpp"
#include "Ball.hpp"
#include "Projectile.hpp"
#include "World.hpp"
#include "Camera/CameraComponent.hpp"
#include "Components/InputComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/SphereComponent.hpp"
#include "Components/MeshComponent.hpp"
#include "Components/PointLightComponent.hpp"
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

		constexpr auto plane = 100_f;
		constexpr auto size = 3;
		
		const Path floor_mesh = u8"../Engine/Assets/Plane.omesh"sv;
		const Path floor_mat = u8"../Assets/Floor.omat"sv;
		
		floor_.SetMesh(floor_mesh);
		floor_.SetRelScale({All{}, 10});
		floor_.SetMaterial(floor_mat);

		constexpr auto base = -plane/2 * ToFloat(size-1);

		for (auto i=0; i<size; ++i)
		{
			for (auto j=0; j<size; ++j)
			{
				const auto floor = AddComponent<MeshComponent>();
				floor->AttachTo(&floor_, AttachRule::kKeepRelative);
				floor->SetMesh(floor_mesh);
				floor->SetRelPos({base+i*plane, base+j*plane});
				floor->SetMaterial(floor_mat);
			}
		}

		const auto point = AddComponent<PointLightComponent>();
		point->AttachTo(&camera_, AttachRule::kKeepRelative);
		
		const auto spot = AddComponent<SpotLightComponent>();
		spot->AttachTo(&camera_, AttachRule::kKeepRelative);
	}

	void ACharacter::OnUpdate(Float)
	{
		floor_.SetRelPos(GetPos() + Vec3{0, 0, -100});
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
