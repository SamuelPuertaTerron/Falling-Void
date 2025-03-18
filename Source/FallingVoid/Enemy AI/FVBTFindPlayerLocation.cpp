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
    // Initialize the task
    return EBTNodeResult::InProgress; // Task will continue to tick
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

    AFVEnemyBase* Enemy = Cast<AFVEnemyBase>(AIController->GetPawn());
    if (!Enemy)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AttackRangeKey.SelectedKeyName, Enemy->AttackRange);

    // Get the enemy location
    FVector EnemyLocation = Enemy->GetActorLocation();

    // Variables for tracking the closest player
    AFVPlayerBase* ClosestPlayer = nullptr;
    float ClosestDistance = FLT_MAX; // Correctly initialize

    float Distance = 0.0f;

    // Get the world safely
    UWorld* World = GetWorld();
    if (!World)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // Iterate over all player controllers
    for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* Controller = Iterator->Get();
        if (!Controller) continue;

        AFVPlayerBase* PlayerCharacter = Cast<AFVPlayerBase>(Controller->GetPawn());
        if (!PlayerCharacter)
            continue;

        Distance = FVector::Dist(EnemyLocation, PlayerCharacter->GetActorLocation());

        // Check if this player is closer
        if (Distance < ClosestDistance)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerKey.SelectedKeyName, PlayerCharacter);
            ClosestDistance = Distance;
            ClosestPlayer = PlayerCharacter;
        }
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitDuration.SelectedKeyName, Enemy->AttackTime);

    if (ClosestPlayer)
    {
        if (ClosestPlayer->GetIsDeadOrDowned())
        {
            FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
            return;
        }

        FVector TargetLocation;

        // If Ranged Enemy the enemy will stay a certain distance from the player
        if (IsRangedEnemy)
        {
            if (Distance > Enemy->AttackRange * RangeAmountModifier)
            {
                TargetLocation = ClosestPlayer->GetActorLocation();
                OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);
            }
            else
            {
                // Calculate the new target position behind the attack range
                FVector direction = (EnemyLocation - ClosestPlayer->GetActorLocation()).GetSafeNormal();
                TargetLocation = ClosestPlayer->GetActorLocation() + (direction * Enemy->AttackRange);

                // Set the player's location in the blackboard
                OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);
            }
        }
        else if (!IsRangedEnemy)
        {
            TargetLocation = ClosestPlayer->GetActorLocation();

            // If search random is enabled, find a random point around the player
            if (SearchRandom)
            {
                FNavLocation NavLocation;
                if (UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(World))
                {
                    if (NavSystem->GetRandomPointInNavigableRadius(TargetLocation, SearchRadius, NavLocation))
                    {
                        TargetLocation = NavLocation.Location;
                    }
                }
            }

            // Set the player's location in the blackboard
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);
        }
    }
    else
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Moving To Player"));

    // Continue ticking
    //FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
}