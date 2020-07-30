#include "FireBallsGame.hpp"
#include "Ball.hpp"
#include "Character.hpp"
#include "Debug.hpp"
#include "Log.hpp"
#include "World.hpp"
#include "Actors/DirLight.hpp"
#include "Actors/SkyLight.hpp"

namespace fb
{
	AFireBallsGame::AFireBallsGame(World& world)
		:AActor{world}
	{
		world.SpawnActor<ASkyLight>();
		
		const auto sun = world.SpawnActor<ADirLight>();
		sun->SetRot({UVec3::right, 70_deg});
	}

	void AFireBallsGame::OnBallDestroy()
	{
		num_balls_ = Max(0, num_balls_ - 1);
	}

	void AFireBallsGame::OnBeginPlay()
	{
		StartGame();
	}

	void AFireBallsGame::OnUpdate([[maybe_unused]] Float delta_seconds)
	{
		constexpr auto max_balls = 10;
		const auto chr = character_.lock();
		
		if (!chr)
		{
			const auto dur = duration_cast<time::seconds>(Clock::now() - start_);
			log::Info(u8"You survived for {} seconds!"sv, dur.count());
			CleanGame();
			StartGame();
			return;
		}
		
		if (num_balls_ < max_balls)
		{
			const auto ball = GetWorld().SpawnActor<ABall>(*this);
			ball->SetPos(chr->GetPos() + Vec3{*UVec2::Rand() * Rand(2000_f, 3000_f)});
			ball->SetTarget(character_);
			ball->AddTag(kTransientTag);
			++num_balls_;
		}
	}

	void AFireBallsGame::StartGame()
	{
		const auto chr = GetWorld().SpawnActor<ACharacter>();
		chr->AddTag(kTransientTag);
		chr->SetPos({0, 0, 10});
		character_ = chr;
		start_ = Clock::now();
	}

	void AFireBallsGame::CleanGame()
	{
		const Name tag = kTransientTag;
		GetWorld().ForEachActor([&](AActor& actor)
		{
			if (actor.HasTag(tag)) actor.Destroy();
		});
		num_balls_ = 0;
	}
}
