#include "Projectile.hpp"
#include "Components/MeshComponent.hpp"
#include "Components/SphereComponent.hpp"

namespace fb
{
	AProjectile::AProjectile(World& world)
		:AActor{world},
		mesh_{AddComponent<MeshComponent>()},
		collision_{AddComponent<SphereComponent>()}
	{
		SetRootComponent(&mesh_);
		mesh_.SetMesh(u8"../Engine/Assets/Sphere.omesh"sv);
		mesh_.SetRelScale({All{}, 0.5_f});

		collision_.AttachTo(&mesh_, AttachRule::kKeepRelative);
		collision_.SetUnscaledRadius(mesh_.GetUnscaledRadius());
		collision_.AddOnOverlap([this](SphereComponent&) { Destroy(); });

		SetLifespan(3);
		AddTag(kTransientTag);
	}

	void AProjectile::OnUpdate(Float delta_seconds)
	{
		SetPos(GetPos() + *GetForward() * (1000 * delta_seconds));
	}
}
