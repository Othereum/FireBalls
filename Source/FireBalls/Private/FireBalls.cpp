#include "Engine.hpp"
#include "FireBallsGame.hpp"

using namespace fb;

DEFINE_GAME_MODULE(Fire Balls);

GAME_API void GameMain(Engine& engine)
{
	engine.GetWorld().SpawnActor<AFireBallsGame>();
}
