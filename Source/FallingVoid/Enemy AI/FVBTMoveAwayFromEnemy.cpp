// Copyright: Falling Void Studios


#include "FVBTMoveAwayFromEnemy.h"
#include "Characters/FVPlayerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "AIController.h"
#include "NavigationSystem.h"

UFVBTMoveAwayFromEnemy::UFVBTMoveAwayFromEnemy()
{
	NodeName = TEXT("Move Away From Player");
}

EBTNodeResult::Type UFVBTMoveAwayFromEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AFVPlayerBase* player = Cast<AFVPlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName));
    if (!player)
        return EBTNodeResult::Failed;
    if (player->GetIsDeadOrDowned())
        return EBTNodeResult::Failed;

    AAIController* aiController = OwnerComp.GetAIOwner();
    if (!aiController)
        return EBTNodeResult::Failed;

    AFVEnemyBase* enemy = Cast<AFVEnemyBase>(aiController->GetPawn());
    if (!enemy)
        return EBTNodeResult::Failed;

    FVector enemyLocation = enemy->GetActorLocation();
    FVector playerLocation = player->GetActorLocation();

    FVector moveAwayFromPlayerDirection = (enemyLocation - playerLocation).GetSafeNormal();
    FVector moveTargetLocation = enemyLocation + moveAwayFromPlayerDirection * FMath::RandRange(MoveAwayRadiusMin, MoveAwayRadiusMax);

    if (UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
    {
        FNavLocation navLocation;
        if (navSystem->GetRandomPointInNavigableRadius(moveTargetLocation, FMath::RandRange(100.0f, 300.0f), navLocation))
        {
            moveTargetLocation = navLocation.Location;
        }
    }

    //Set the player to be nullptr so that the player is no longer in range of this enemy
    OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerKey.SelectedKeyName, nullptr);
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, moveTargetLocation);

    return EBTNodeResult::Succeeded;
}