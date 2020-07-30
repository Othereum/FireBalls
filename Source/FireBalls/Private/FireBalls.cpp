#include "Engine.hpp"
#include "FireBallsGame.hpp"

DEFINE_GAME_MODULE(Fire Balls);

GAME_API void GameMain(oeng::Engine& engine)
{
	engine.GetWorld().SpawnActor<fb::AFireBallsGame>();
}
