// Copyright: Falling Void Studios


#include "Enemy AI/FVBTMoveAwayFromPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "FVEnemyAIController.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"

UFVBTMoveAwayFromPlayer::UFVBTMoveAwayFromPlayer()
{
	NodeName = "Move Away from Player";
}

EBTNodeResult::Type UFVBTMoveAwayFromPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	if (!player)
	{
		return EBTNodeResult::Failed;
	}

	if (player->GetIsDeadOrDowned())
	{
		return EBTNodeResult::Failed;
	}

	FVector enemyLocation = enemy->GetActorLocation();
	FVector playerLocation = player->GetActorLocation();

	// Calculate retreat direction (away from player)
	FVector awayFromPlayer = (enemyLocation - playerLocation).GetSafeNormal();

	// Add some randomness to avoid predictable movement
	FVector randomOffset = FMath::VRand() * FMath::FRandRange(0.f, RetreatRandomness);
	randomOffset.Z = 0.f;

	// Calculate target location
	FVector targetLocation = enemyLocation + (awayFromPlayer * RetreatDistance) + randomOffset;

	controller->SetControlRotation(targetLocation.Rotation());
	enemy->GetMesh()->SetWorldRotation(targetLocation.Rotation());

	controller->MoveToLocation(targetLocation);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(RetreatKey.SelectedKeyName, true);

	return EBTNodeResult::Succeeded;
}
