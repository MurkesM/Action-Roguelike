// Fill out your copyright notice in the Description page of Project Settings.

#include "SGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "AI/SAICharacter.h"
#include "EngineUtils.h"
#include "SPlayerState.h"
#include "SCharacter.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), true, TEXT("Enable spawning of bots via timer."), ECVF_Cheat);

ASGameModeBase::ASGameModeBase()
{
	SpawnTimerInterval = 2;
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ASGameModeBase::SpawnBotTimerElaped, SpawnTimerInterval, true);
}

void ASGameModeBase::OnActorKilled(AActor* KilledActor, AActor* ActorKiller)
{
	ASCharacter* KilledPlayer = Cast<ASCharacter>(KilledActor);

	//handle player death
	if (KilledPlayer)
	{
		FTimerHandle TimerHandle_RespawnDelay;

		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, "RespawnPlayerElapsed", KilledPlayer->GetController());

		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, TimerDelegate, 2.0f, false);
	}

	//handle bot death
	else
	{
		ASAICharacter* KilledBot = Cast<ASAICharacter>(KilledActor);
		ASCharacter* KillerPlayer = Cast<ASCharacter>(ActorKiller);

		if (KilledBot && KillerPlayer)
		{
			APlayerState* PlayerState = KillerPlayer->GetPlayerState();

			if (PlayerState)
			{
				ASPlayerState* SPlayerState = Cast<ASPlayerState>(PlayerState);

				if (SPlayerState)
				{
					SPlayerState->AddCredits(1);
				}
			}
		}
	}
}

void ASGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if (Controller)
	{
		Controller->UnPossess();

		RestartPlayer(Controller);
	}
}

void ASGameModeBase::SpawnBotTimerElaped()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot spawning disabled via cvar 'CVARSpawnBots'."));
		return;
	}

	int32 AliveBotsAmount = 0;

	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* Bot = *It;

		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Bot);

		if (AttributeComp && AttributeComp->IsAlive())
		{
			AliveBotsAmount++;
		}
	}

	float MaxBotCount = 10;

	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (AliveBotsAmount >= MaxBotCount)
	{
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryCompleted);
	}
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn both EQS Query Failed!"))
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		AActor* NewMinion = GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
	}
}

void ASGameModeBase::KillAllAI()
{
	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* Bot = *It;

		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Bot);

		if (AttributeComp && AttributeComp->IsAlive())
		{
			AttributeComp->Kill(this);
		}
	}
}