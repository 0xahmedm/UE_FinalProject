// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

class AEnemyCharacter;
class ABaseCharacter;

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	TSubclassOf<AEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 EnemyCount = 3;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllWavesComplete);

UCLASS()
class FINALPROJECT_API AWaveManager : public AActor
{
	GENERATED_BODY()

public:
	AWaveManager();

	// List of waves in order
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waves")
	TArray<FWaveData> Waves;

	// Optional spawn points. If empty, enemies spawn around the WaveManager actor.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waves")
	TArray<AActor*> SpawnPoints;

	// Used when SpawnPoints is empty
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waves")
	float FallbackSpawnRadius = 1500.f;

	// Delay before the next wave starts (also delays first wave)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waves")
	float DelayBetweenWaves = 2.f;

	UPROPERTY(BlueprintAssignable, Category = "Waves")
	FOnAllWavesComplete OnAllWavesComplete;

	UFUNCTION(BlueprintPure, Category = "Waves")
	int32 GetCurrentWaveNumber() const { return CurrentWaveIndex + 1; }

	UFUNCTION(BlueprintPure, Category = "Waves")
	int32 GetTotalWaves() const { return Waves.Num(); }

protected:
	virtual void BeginPlay() override;

private:
	int32 CurrentWaveIndex = -1;
	int32 EnemiesAlive = 0;

	FTimerHandle WaveTimerHandle;

	void StartNextWave();
	void SpawnWave(const FWaveData& Wave);

	UFUNCTION()
	void HandleEnemyDied(ABaseCharacter* DeadCharacter);
};
