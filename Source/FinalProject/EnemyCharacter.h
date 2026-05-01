// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"


UCLASS()
class FINALPROJECT_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

	// How much damage this enemy deals per hit
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackDamage = 5.f;

	// How close the enemy must be to attack
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackRange = 150.f;

	// Cooldown between attacks in seconds
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackCooldown = 2.0f;

	// Called by the Behavior Tree task to perform the attack
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void PerformAttack();

	// Is the enemy currently on cooldown?
	bool bCanAttack = true;

protected:
	virtual void BeginPlay() override;
	virtual void OnDeath() override;

private:
	FTimerHandle AttackTimerHandle;
	void ResetAttackCooldown();
};
