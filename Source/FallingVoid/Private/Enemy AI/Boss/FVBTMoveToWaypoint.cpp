// Copyright: Falling Void Studios


#include "Enemy AI/Boss/FVBTMoveToWaypoint.h"

#include "FVEnemyAIController.h"
#include "FVWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "Kismet/GameplayStatics.h"

UFVBTMoveToWaypoint::UFVBTMoveToWaypoint()
{
	NodeName = "Move to Waypoint";
}

EBTNodeResult::Type UFVBTMoveToWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	AFVEnemyBase* enemy = Cast<AFVEnemyBase>(controller->GetPawn());
	if (!enemy)
	{
		return EBTNodeResult::Failed;
	}

	AFVWaypoint* waypoint = Cast<AFVWaypoint>(UGameplayStatics::GetActorOfClass(GetWorld(), AFVWaypoint::StaticClass()));
	if (!waypoint)
	{
		return EBTNodeResult::Failed;
	}

	controller->MoveToLocation(waypoint->GetActorLocation(), Radius);

	blackboard->SetValueAsBool(CanAttackKey.SelectedKeyName, true); //The enemy can now attack

	return EBTNodeResult::Succeeded;
}
