#include "Ball.hpp"
#include "FireBallsGame.hpp"
#include "Projectile.hpp"
#include "Components/MeshComponent.hpp"
#include "Components/SphereComponent.hpp"

namespace fb
{
	ABall::ABall(World& world, AFireBallsGame& game)
		:AActor{world},
		game_{game},
		mesh_{AddComponent<MeshComponent>()},
		collision_{AddComponent<SphereComponent>()},
		hp_{ 5 }
	{
		SetRootComponent(&mesh_);
		mesh_.SetMesh(u8"../Engine/Assets/Sphere.omesh"sv);
		mesh_.SetRelScale({All{}, 5});

		collision_.AttachTo(&mesh_, AttachRule::kKeepRelative);
		collision_.SetUnscaledRadius(mesh_.GetUnscaledRadius());
		
		collision_.AddOnOverlap([this](SphereComponent& other)
		{
			if (dynamic_cast<AProjectile*>(&other.GetOwner()) && --hp_ <= 0)
			{
				game_.OnBallDestroy();
				Destroy();
			}
		});
	}
}
