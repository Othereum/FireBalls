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
		mesh_{*AddComponent<MeshComponent>()},
		collision_{*AddComponent<SphereComponent>()},
		hp_{ 3 }
	{
		SetRootComponent(&mesh_);
		mesh_.SetMesh(u8"../Engine/Assets/Sphere.omesh"sv);
		mesh_.SetRelScale({All{}, 5});

		collision_.AttachTo(&mesh_, AttachRule::kKeepRelative);
		collision_.SetUnscaledRadius(mesh_.GetUnscaledRadius());
		
		collision_.AddOnOverlap([this](SphereComponent& other)
		{
			if (dynamic_cast<AProjectile*>(&other.GetOwner()))
			{
				if (--hp_ <= 0)
				{
					game_.OnBallKilled();
					Destroy();
				}
			}
		});
	}

	void ABall::OnUpdate(Float delta_seconds)
	{
		if (const auto target = target_.lock())
		{
			auto dir = target->GetPos() - GetPos();
			dir.TryNormalize();
			SetPos(GetPos() + dir * (330 * delta_seconds));
		}
	}
}
