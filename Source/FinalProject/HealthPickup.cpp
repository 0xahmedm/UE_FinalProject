// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseCharacter.h"

// Sets default values
AHealthPickup::AHealthPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Collision sphere — detects when player walks over it
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(70.f);
	RootComponent = CollisionSphere;

	// Visual mesh
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(RootComponent);

	// Bind overlap event
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(
		this, &AHealthPickup::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthPickup::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// Only heal BaseCharacter subclasses (player + enemies)
	ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor);
	if (Character && !Character->IsDead())
	{
		Character->HealCharacter(HealAmount);
		Destroy(); // Consume the pickup
	}
}