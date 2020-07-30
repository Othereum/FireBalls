#include "FireBallsGame.hpp"
#include "Ball.hpp"
#include "Character.hpp"
#include "World.hpp"
#include "Actors/DirLight.hpp"
#include "Actors/SkyLight.hpp"

namespace fb
{
	AFireBallsGame::AFireBallsGame(World& world)
		:AActor{world},
		character_{world.SpawnActor<ACharacter>()}
	{
		world.SpawnActor<ASkyLight>();
		world.SpawnActor<ADirLight>();
		SpawnBall();
	}

	void AFireBallsGame::SpawnBall()
	{
		auto& ball = GetWorld().SpawnActor<ABall>();
		ball.SetTrsf({
			{200, 75, 0},
			Quat{UVec3::up, 225_deg} * Quat{UVec3::right, -90_deg},
			{All{}, 2}
		});
		balls_.emplace_back(ball);
	}
}
