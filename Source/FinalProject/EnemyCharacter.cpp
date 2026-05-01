// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "AIController.h"
#include "BrainComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Enemies rotate toward movement direction automatically
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::PerformAttack()
{
	if (!bCanAttack || IsDead()) return;

	// Find the player and damage them
	AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Player) return;

	float DistToPlayer = FVector::Dist(GetActorLocation(), Player->GetActorLocation());

	if (DistToPlayer <= AttackRange)
	{
		UGameplayStatics::ApplyDamage(
			Player,
			AttackDamage,
			GetController(),
			this,
			UDamageType::StaticClass()
		);
	}

	// Start cooldown
	bCanAttack = false;
	GetWorldTimerManager().SetTimer(
		AttackTimerHandle,    // We need to declare this — see below
		this,
		&AEnemyCharacter::ResetAttackCooldown,
		AttackCooldown,
		false
	);
}

void AEnemyCharacter::ResetAttackCooldown()
{
	bCanAttack = true;
}

void AEnemyCharacter::OnDeath()
{
	// Stop the Behavior Tree first so the AI can't keep ticking attacks during the 2s destroy delay
	if (AAIController* AICon = Cast<AAIController>(GetController()))
	{
		if (AICon->GetBrainComponent())
		{
			AICon->GetBrainComponent()->StopLogic(TEXT("Dead"));
		}
		AICon->UnPossess();
	}

	// Run base (stops movement, disables collision, sets lifespan = 2s)
	Super::OnDeath();
}