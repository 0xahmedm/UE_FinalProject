// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackPlayer.h"

#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AttackPlayer::UBTTask_AttackPlayer()
{
	NodeName = TEXT("Attack Player");
}

EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	AEnemyAIController* AIController = 
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    
	if (!AIController) return EBTNodeResult::Failed;

	AEnemyCharacter* Enemy = 
		Cast<AEnemyCharacter>(AIController->GetPawn());
    
	if (!Enemy || Enemy->IsDead()) return EBTNodeResult::Failed;

	if (!Enemy->bCanAttack) return EBTNodeResult::Failed;

	// Call the attack on the enemy
	Enemy->PerformAttack();

	return EBTNodeResult::Succeeded;
}