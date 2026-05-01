// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

// Define the key name constants — these must match your Blackboard asset
const FName AEnemyAIController::BlackboardKey_TargetPlayer(TEXT("TargetPlayer"));
const FName AEnemyAIController::BlackboardKey_CanAttack(TEXT("CanAttack"));

AEnemyAIController::AEnemyAIController()
{
	// Unreal requires this to use Blackboard
	bWantsPlayerState = false;
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		// Start the Blackboard and Behavior Tree
		RunBehaviorTree(BehaviorTree);

		// Set the player as the target immediately
		AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (Player)
		{
			GetBlackboardComponent()->SetValueAsObject(
				BlackboardKey_TargetPlayer, Player);
		}
	}
}