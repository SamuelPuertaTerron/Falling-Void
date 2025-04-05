// Copyright: Falling Void Studios


#include "Enemy AI/FVBTAttackPlayer.h"

#include "FVEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
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

	enemy->Attack();
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(LastAttackTIme.SelectedKeyName, GetWorld()->GetDeltaSeconds());
	UE_LOG(LogTemp, Warning, TEXT("Attacked Player"));

	return EBTNodeResult::Succeeded;
}
