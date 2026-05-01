// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FinalProjectGameMode.h"
#include "WaveGameMode.generated.h"

class AWaveManager;

UCLASS()
class FINALPROJECT_API AWaveGameMode : public AFinalProjectGameMode
{
	GENERATED_BODY()

public:
	AWaveGameMode();

	// Class of WaveManager to spawn at game start
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waves")
	TSubclassOf<AWaveManager> WaveManagerClass;

	// Called by the player character when it dies
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void HandlePlayerDeath();

	UFUNCTION(BlueprintPure, Category = "Waves")
	AWaveManager* GetWaveManager() const { return WaveManager; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	AWaveManager* WaveManager = nullptr;

	UFUNCTION()
	void HandleAllWavesComplete();
};
