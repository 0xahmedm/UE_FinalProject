// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"


UCLASS()
class FINALPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();

	// Called when this controller possesses a pawn (enemy spawns)
	virtual void OnPossess(APawn* InPawn) override;

	// Blackboard key names — must match exactly what you set in the BB asset
	static const FName BlackboardKey_TargetPlayer;
	static const FName BlackboardKey_CanAttack;

protected:
	// The Behavior Tree asset to run — assign in Blueprint
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;
};
