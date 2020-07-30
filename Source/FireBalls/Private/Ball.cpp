#include "Ball.hpp"
#include "Components/MeshComponent.hpp"

namespace fb
{
	ABall::ABall(World& world)
		:AActor{world},
		mesh_{AddComponent<MeshComponent>()}
	{
		SetRootComponent(&mesh_);
		mesh_.SetMesh(u8"../Engine/Assets/Sphere.omesh"sv);
	}
}
