// Fill out your copyright notice in the Description page of Project Settings.

#include "WaveGameMode.h"
#include "WaveManager.h"
#include "CombatHUD.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"

AWaveGameMode::AWaveGameMode()
{
	HUDClass = ACombatHUD::StaticClass();
}

void AWaveGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Prefer a WaveManager already placed in the level so the level designer
	// can position it and configure SpawnPoints there.
	for (TActorIterator<AWaveManager> It(GetWorld()); It; ++It)
	{
		WaveManager = *It;
		break;
	}

	if (!WaveManager && WaveManagerClass)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		WaveManager = GetWorld()->SpawnActor<AWaveManager>(
			WaveManagerClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
	}

	if (WaveManager)
	{
		WaveManager->OnAllWavesComplete.AddDynamic(this, &AWaveGameMode::HandleAllWavesComplete);
	}
}

void AWaveGameMode::HandlePlayerDeath()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	if (ACombatHUD* HUD = Cast<ACombatHUD>(PC->GetHUD()))
	{
		HUD->ShowLoseScreen();
	}
}

void AWaveGameMode::HandleAllWavesComplete()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	if (ACombatHUD* HUD = Cast<ACombatHUD>(PC->GetHUD()))
	{
		HUD->ShowWinScreen();
	}
}
