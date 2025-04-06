// Copyright: Falling Void Studios


#include "Enemy AI/FVBTIsPlayerInAttackRange.h"

#include "FVEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"

bool UFVBTIsPlayerInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(OwnerComp.GetAIOwner());
	if (!controller)
	{
		return false;
	}

	AFVEnemyBase* enemy = Cast<AFVEnemyBase>(controller->GetPawn());
	if (!enemy)
	{
		return false;
	}

	AFVPlayerBase* player = Cast<AFVPlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName));
	if (!player)
	{
		return false;
	}

	if (player->GetIsDeadOrDowned())
	{
		return false;
	}

	FVector playerLocation = player->GetActorLocation();
	FVector enemyLocation = enemy->GetActorLocation();

	float distance = FVector::Distance(playerLocation, enemyLocation);

	return distance <= enemy->AttackRange;
}
