// Fill out your copyright notice in the Description page of Project Settings.

#include "WaveManager.h"
#include "EnemyCharacter.h"
#include "BaseCharacter.h"
#include "TimerManager.h"
#include "Engine/World.h"

AWaveManager::AWaveManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	// Kick off the first wave after the configured delay
	GetWorldTimerManager().SetTimer(
		WaveTimerHandle, this, &AWaveManager::StartNextWave,
		FMath::Max(0.01f, DelayBetweenWaves), false);
}

void AWaveManager::StartNextWave()
{
	CurrentWaveIndex++;

	if (!Waves.IsValidIndex(CurrentWaveIndex))
	{
		// All waves cleared
		OnAllWavesComplete.Broadcast();
		return;
	}

	SpawnWave(Waves[CurrentWaveIndex]);
}

void AWaveManager::SpawnWave(const FWaveData& Wave)
{
	if (!Wave.EnemyClass || Wave.EnemyCount <= 0)
	{
		// Skip empty / invalid wave entries
		StartNextWave();
		return;
	}

	EnemiesAlive = 0;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int32 i = 0; i < Wave.EnemyCount; ++i)
	{
		FVector SpawnLoc;
		FRotator SpawnRot = FRotator::ZeroRotator;

		if (SpawnPoints.Num() > 0)
		{
			AActor* Pt = SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)];
			if (!Pt) continue;
			SpawnLoc = Pt->GetActorLocation();
			SpawnRot = Pt->GetActorRotation();
		}
		else
		{
			FVector Off = FMath::VRand() * FMath::FRandRange(0.f, FallbackSpawnRadius);
			Off.Z = 0.f;
			SpawnLoc = GetActorLocation() + Off;
		}

		AEnemyCharacter* Enemy = GetWorld()->SpawnActor<AEnemyCharacter>(
			Wave.EnemyClass, SpawnLoc, SpawnRot, SpawnParams);

		if (Enemy)
		{
			Enemy->SpawnDefaultController();
			Enemy->OnDied.AddDynamic(this, &AWaveManager::HandleEnemyDied);
			EnemiesAlive++;
		}
	}

	if (EnemiesAlive == 0)
	{
		// Nothing actually spawned (e.g. all SpawnPoints null) — advance immediately
		StartNextWave();
	}
}

void AWaveManager::HandleEnemyDied(ABaseCharacter* /*DeadCharacter*/)
{
	EnemiesAlive = FMath::Max(0, EnemiesAlive - 1);

	if (EnemiesAlive == 0)
	{
		GetWorldTimerManager().SetTimer(
			WaveTimerHandle, this, &AWaveManager::StartNextWave,
			FMath::Max(0.01f, DelayBetweenWaves), false);
	}
}
