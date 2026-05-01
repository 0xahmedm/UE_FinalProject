// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Start at full health
	CurrentHealth = MaxHealth;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABaseCharacter::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
	// Always call Super first — Unreal expects it
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.f && !IsDead())
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - ActualDamage, 0.f, MaxHealth);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 4.f, FColor::Red,
				FString::Printf(TEXT("%s took %.0f dmg (HP: %.0f / %.0f)"),
				*GetName(), ActualDamage, CurrentHealth, MaxHealth));
		}

		if (IsDead())
		{
			OnDeath();
		}
	}

	return ActualDamage;
}

bool ABaseCharacter::IsDead() const
{
	return CurrentHealth <= 0.f;
}

void ABaseCharacter::HealCharacter(float Amount)
{
	if (!IsDead())
	{
		CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.f, MaxHealth);
	}
}

void ABaseCharacter::OnDeath()
{
	// Stop all movement immediately
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->StopMovementImmediately();

	// Disable capsule collision so nothing interacts with the corpse
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Notify listeners (WaveManager, etc.)
	OnDied.Broadcast(this);

	// Auto-destroy after 2 seconds
	SetLifeSpan(2.f);
}