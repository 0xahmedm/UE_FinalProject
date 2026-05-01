// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPackSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

// Sets default values
AHealthPackSpawner::AHealthPackSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AHealthPackSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnPacks();
}

// Called every frame
void AHealthPackSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthPackSpawner::SpawnPacks()
{
	if (!PickupClass) return;

	for (int32 i = 0; i < SpawnCount; i++)
	{
		// Pick a random point in a circle around the spawner
		FVector RandomOffset = FMath::VRand() * FMath::RandRange(800.f, SpawnRadius);
		RandomOffset.Z = 0.f; // Keep it flat

		FVector SpawnLocation = GetActorLocation() + RandomOffset;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		GetWorld()->SpawnActor<AActor>(PickupClass, SpawnLocation,
			FRotator::ZeroRotator, SpawnParams);
	}
}