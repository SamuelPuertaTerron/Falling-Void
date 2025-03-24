// Copyright: Falling Void Studios

#include "FVBTFindPlayerLocation.h"

#include "FVGlobals.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UFVBTFindPlayerLocation::UFVBTFindPlayerLocation()
{
    NodeName = TEXT("Find Player Location");
    bNotifyTick = true; // Enable ticking for this task
}

EBTNodeResult::Type UFVBTFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    /*// Get the AI controller and its pawn
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }

    AFVEnemyBase* enemy = Cast<AFVEnemyBase>(AIController->GetPawn());
    if (!enemy)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AttackRangeKey.SelectedKeyName, enemy->AttackRange);
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitDuration.SelectedKeyName, enemy->AttackTime);

    AFVPlayerBase* player = Cast<AFVPlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName));
    if (!player)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }

    float Distance = FVector::Dist(enemy->GetActorLocation(), player->GetActorLocation());
    FVector targetLocation = player->GetActorLocation();

    if (IsRangedEnemy)
    {
        if (Distance > enemy->AttackRange * RangeAmountModifier)
        {
            targetLocation = player->GetActorLocation();
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetLocation);
        }
        else
        {
            // Calculate the new target position behind the attack range
            FVector direction = (enemy->GetActorLocation() - player->GetActorLocation()).GetSafeNormal();
            targetLocation = player->GetActorLocation() + (direction * enemy->AttackRange);

            // Set the player's location in the blackboard
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetLocation);
        }
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetLocation);
    }


    UE_LOG(LogTemp, Warning, TEXT("Moving To Player with his location being %s"), *targetLocation.ToString());*/

    // Continue ticking
    FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
    return EBTNodeResult::InProgress;
}

void UFVBTFindPlayerLocation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    // Get the AI controller and its pawn
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool("CanMove"))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    AFVEnemyBase* enemy = Cast<AFVEnemyBase>(AIController->GetPawn());
    if (!enemy)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AttackRangeKey.SelectedKeyName, enemy->AttackRange);
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitDuration.SelectedKeyName, enemy->AttackTime);

    AFVPlayerBase* player = Cast<AFVPlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName));
    if (!player)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    float Distance = FVector::Dist(enemy->GetActorLocation(), player->GetActorLocation());
    FVector targetLocation = player->GetActorLocation();

    if (IsRangedEnemy)
    {
        if (Distance > enemy->AttackRange * RangeAmountModifier)
        {
            targetLocation = player->GetActorLocation();
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetLocation);
        }
        else
        {
            // Calculate the new target position behind the attack range
            FVector direction = (enemy->GetActorLocation() - player->GetActorLocation()).GetSafeNormal();
            targetLocation = player->GetActorLocation() + (direction * enemy->AttackRange);

            // Set the player's location in the blackboard
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetLocation);
        }
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetLocation);
    }


    UE_LOG(LogTemp, Warning, TEXT("Moving To Player with his location being %s"), *targetLocation.ToString());
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
