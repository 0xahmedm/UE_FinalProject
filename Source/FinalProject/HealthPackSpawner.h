// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPackSpawner.generated.h"

UCLASS()
class FINALPROJECT_API AHealthPackSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPackSpawner();
	
	// The pickup class to spawn
	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<AActor> PickupClass;

	// How far from the spawner center packs can appear
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnRadius = 2000.f;

	// How many packs to spawn
	UPROPERTY(EditAnywhere, Category = "Spawner")
	int32 SpawnCount = 10;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnPacks();
};
