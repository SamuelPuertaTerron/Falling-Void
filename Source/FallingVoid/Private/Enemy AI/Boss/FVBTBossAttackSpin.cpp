// Copyright: Falling Void Studios


#include "Enemy AI/Boss/FVBTBossAttackSpin.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "FVEnemyAIController.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVBossEnemy.h"

UFVBTBossAttackSpin::UFVBTBossAttackSpin()
{
	NodeName = "Attack Spin";
}

EBTNodeResult::Type UFVBTBossAttackSpin::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if (!blackboard)
	{
		UE_LOG(LogTemp, Error, TEXT("Blackboard is null or invalid!"));
		return EBTNodeResult::Failed;
	}

	AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(OwnerComp.GetAIOwner());
	if (!controller)
	{
		UE_LOG(LogTemp, Error, TEXT("Controller is null or invalid!"));
		return EBTNodeResult::Failed;
	}

	AFVBossEnemy* enemy = Cast<AFVBossEnemy>(controller->GetPawn());
	if (!enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy is null or invalid!"));
		return EBTNodeResult::Failed;
	}

	enemy->IsComboCAttacking = true;

	return EBTNodeResult::Succeeded;
}


