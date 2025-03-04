// Copyright: Falling Void Studios

#include "FVBTIsPlayerInRange.h"

#include "AIController.h"
#include "FVGlobals.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"

UFVBTIsPlayerInRange::UFVBTIsPlayerInRange()
{
	NodeName = TEXT("Is Player In Range");
}

bool UFVBTIsPlayerInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AFVPlayerBase* player = Cast<AFVPlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName));
	if (!player)
		return false;

	if (player->GetIsDeadOrDowned())
		return false;

	float detection = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(AttackRangeKey.SelectedKeyName);

	AAIController* aiController = OwnerComp.GetAIOwner();
	if (!aiController)
		return false;

	AFVEnemyBase* enemy = Cast<AFVEnemyBase>(aiController->GetPawn());
	if (!enemy)
	{
		return false;
	}

	float distanceToPlayer = FVector::Dist(enemy->GetActorLocation(), player->GetActorLocation());

	return distanceToPlayer <= detection;
}
 