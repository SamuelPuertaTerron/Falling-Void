// Copyright: Falling Void Studios


#include "FVBTMoveAwayFromEnemy.h"
#include "Characters/FVPlayerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "AIController.h"
#include <NavigationSystem.h>

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

	FVector moveAwayFromPlayerDirection = playerLocation - enemyLocation;
	moveAwayFromPlayerDirection.Normalize();

	FVector targetLocation;

	if (UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		FNavLocation NavLocation;
		if (NavSystem->GetRandomPointInNavigableRadius(targetLocation, FMath::RandRange(MoveAwayRadiusMin, MoveAwayRadiusMin), NavLocation)) 
		{
			targetLocation = NavLocation.Location;
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, targetLocation);

	return EBTNodeResult::Succeeded;
}
