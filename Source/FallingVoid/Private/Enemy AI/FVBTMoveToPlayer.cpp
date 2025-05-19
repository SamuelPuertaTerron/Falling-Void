// Copyright: Falling Void Studios


#include "Enemy AI/FVBTMoveToPlayer.h"

#include "FVEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemies/FVBossEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

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

    if (IsBoss)
    {
        AFVBossEnemy* enemy = Cast<AFVBossEnemy>(controller->GetPawn());
        if (!enemy)
        {
            return EBTNodeResult::Failed;
        }

    	UCharacterMovementComponent* movement = enemy->GetCharacterMovement();
        movement->MaxWalkSpeed = enemy->SprintSpeed;
        controller->MoveToLocation(targetLocation, Radius);
    }
    else
    {
        FVector randomOffset = FMath::VRand() * FMath::FRandRange(MinRandomOffset, MaxRandomOffset);
        randomOffset.Z = 0; // Keep movement horizontal
        targetLocation += randomOffset;



        controller->MoveToLocation(targetLocation, Radius);
    }
    
    return EBTNodeResult::Succeeded;
}
