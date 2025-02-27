// Copyright: Falling Void Studios

#include "FVBTFindPlayerLocation.h"

#include "FVGlobals.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"

UFVBTFindPlayerLocation::UFVBTFindPlayerLocation()
{
    NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFVBTFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Get the AI controller and its pawn
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    AFVEnemyBase* Enemy = Cast<AFVEnemyBase>(AIController->GetPawn());
    if (!Enemy) return EBTNodeResult::Failed;

    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AttackRangeKey.SelectedKeyName, Enemy->AttackRange);

    // Get the enemy location
    FVector EnemyLocation = Enemy->GetActorLocation();

    // Variables for tracking the closest player
    AFVPlayerBase* ClosestPlayer = nullptr;
    float ClosestDistance = FLT_MAX; // Correctly initialize

    // Get the world safely
    UWorld* World = GetWorld();
    if (!World) return EBTNodeResult::Failed;

    // Iterate over all player controllers
    for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* Controller = Iterator->Get();
        if (!Controller) continue;

        AFVPlayerBase* PlayerCharacter = Cast<AFVPlayerBase>(Controller->GetPawn());
        if (!PlayerCharacter) 
            continue;

        if (PlayerCharacter->GetIsDeadOrDowned())
            continue;

        float Distance = FVector::Dist(EnemyLocation, PlayerCharacter->GetActorLocation());

        // Check if this player is closer
        if (Distance < ClosestDistance)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerKeySelector.SelectedKeyName, PlayerCharacter);
            ClosestDistance = Distance;
            ClosestPlayer = PlayerCharacter;
        }
    }

    if (ClosestPlayer)
    {
        //FVGlobals::LogToScreen("Closest Player: " + ClosestPlayer->GetName());
        UE_LOG(LogTemp, Warning, TEXT("Closest Player Found: %s"), *ClosestPlayer->GetName());

        FVector TargetLocation = ClosestPlayer->GetActorLocation();

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
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }

    //FVGlobals::LogToScreen("No players found!");
    return EBTNodeResult::Failed;
}
