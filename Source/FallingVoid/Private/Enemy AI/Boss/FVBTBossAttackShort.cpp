// Copyright: Falling Void Studios


#include "Enemy AI/Boss/FVBTBossAttackShort.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "FVEnemyAIController.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVBossEnemy.h"

UFVBTBossAttackShort::UFVBTBossAttackShort()
{
	NodeName = "Boss Attack Short";
}

EBTNodeResult::Type UFVBTBossAttackShort::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if (!blackboard)
	{
		return EBTNodeResult::Failed;
	}

	AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(OwnerComp.GetAIOwner());
	if (!controller)
	{
		return EBTNodeResult::Failed;
	}

	AFVBossEnemy* enemy = Cast<AFVBossEnemy>(controller->GetPawn());
	if (!enemy)
	{
		return EBTNodeResult::Failed;
	}

	AFVPlayerBase* player = Cast<AFVPlayerBase>(blackboard->GetValueAsObject(PlayerKey.SelectedKeyName));
	if (!player || player->GetIsDeadOrDowned())
	{
		return EBTNodeResult::Failed;
	}

	enemy->IsComboAAttacking = true;

	

	return EBTNodeResult::Succeeded;
}