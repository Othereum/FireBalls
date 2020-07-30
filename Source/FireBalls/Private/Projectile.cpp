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
		collision_.SetRadius(mesh_.GetRadius());
	}

	void AProjectile::OnUpdate(Float delta_seconds)
	{
		SetPos(GetPos() + *GetForward() * (1000 * delta_seconds));
	}
}
