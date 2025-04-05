// Copyright: Falling Void Studios


#include "Enemy AI/FVBTMoveToPlayer.h"

#include "FVEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UFVBTMoveToPlayer::UFVBTMoveToPlayer()
{
    NodeName = "Move to Player";
}

EBTNodeResult::Type UFVBTMoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(OwnerComp.GetAIOwner());
    if (!controller)
    {
        return EBTNodeResult::Failed;
    }

    FVector targetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetLocationKey.SelectedKeyName);

    FVector randomOffset = FMath::VRand() * FMath::FRandRange(MinRandomOffset, MaxRandomOffset);
    randomOffset.Z = 0; // Keep movement horizontal
    targetLocation += randomOffset;

    controller->MoveToLocation(targetLocation, Radius);
    return EBTNodeResult::Succeeded;
}
