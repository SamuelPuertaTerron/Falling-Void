// Copyright: Falling Void Studios


#include "Enemy AI/FVBTAttackPlayer.h"

#include "FVEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"

UFVBTAttackPlayer::UFVBTAttackPlayer()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UFVBTAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(OwnerComp.GetAIOwner());
	if (!controller)
	{
		return EBTNodeResult::Failed;
	}

	AFVEnemyBase* enemy = Cast<AFVEnemyBase>(controller->GetPawn());
	if (!enemy)
	{
		return EBTNodeResult::Failed;
	}

	AFVPlayerBase* player = Cast<AFVPlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName));
	if (!player || player->GetIsDeadOrDowned())
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if(!blackboard)
	{
		return EBTNodeResult::Failed;
	}

	controller->SetFocus(player);
	enemy->Attack();
	blackboard->SetValueAsFloat(LastAttackTIme.SelectedKeyName, GetWorld()->GetTimeSeconds()); // Store the attack time in the blackboard

	return EBTNodeResult::Succeeded;
}
