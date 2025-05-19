// Copyright: Falling Void Studios


#include "Enemy AI/FVBTMoveAwayFromPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	FVector awayFromPlayer = (enemyLocation - playerLocation).GetSafeNormal();

	FVector randomOffset = FMath::VRand() * FMath::FRandRange(0.f, RetreatRandomness);
	randomOffset.Z = 0.f;

	FVector targetLocation = enemyLocation + (awayFromPlayer * RetreatDistance) + randomOffset;

	FVector moveDirection = (targetLocation - enemyLocation).GetSafeNormal();
	if (moveDirection.IsNearlyZero())
	{
		return EBTNodeResult::Failed;
	}

	FRotator targetRotation = moveDirection.Rotation();
	targetRotation.Pitch = 0.f;
	targetRotation.Roll = 0.f;


	enemy->GetCharacterMovement()->bOrientRotationToMovement = true;

	controller->SetControlRotation(targetRotation);

	controller->MoveToLocation(targetLocation);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(RetreatKey.SelectedKeyName, true);

	return EBTNodeResult::Succeeded;
}
