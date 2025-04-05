// Copyright: Falling Void Studios


#include "Enemy AI/FVBTFlankPlayer.h"

#include "FVEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"

UFVBTFlankPlayer::UFVBTFlankPlayer()
{
	NodeName = "Flank Player";
}

EBTNodeResult::Type UFVBTFlankPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	FVector playerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetLocationKey.SelectedKeyName);
	FVector playerForward = player->GetActorForwardVector();
	FVector playerRight = player->GetActorRightVector();

	FVector leftFlankPos = playerLocation + (playerRight * -FlankRadius) + (playerForward * FlankRadius);
	FVector rightFlankPos = playerLocation + (playerRight * FlankRadius) + (playerForward * FlankRadius);

	float distToLeft = FVector::Dist(enemy->GetActorLocation(), leftFlankPos);
	float distToRight = FVector::Dist(enemy->GetActorLocation(), rightFlankPos);

	FVector targetFlankPos = distToLeft > distToRight ? leftFlankPos : rightFlankPos;

	targetFlankPos += FMath::VRand() * (FlankRadius * 0.3f);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, targetFlankPos);

	return EBTNodeResult::Type();
}
