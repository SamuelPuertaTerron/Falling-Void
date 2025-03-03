// Copyright: Falling Void Studios

#include "FVBTIsPlayerInRange.h"

#include "AIController.h"
#include "FVGlobals.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/FVBaseCharacter.h"
#include "Characters/Enemies/FVEnemyBase.h"

UFVBTIsPlayerInRange::UFVBTIsPlayerInRange()
{
	NodeName = TEXT("Is Player In Range");
}

bool UFVBTIsPlayerInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AFVBaseCharacter* player = Cast<AFVBaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName));
	if (!player)
		return false;


	float dection = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(AttackRangeKey.SelectedKeyName);

	AAIController* aiController = OwnerComp.GetAIOwner();
	if (!aiController)
		return false;

	AFVEnemyBase* enemy = Cast<AFVEnemyBase>(aiController->GetPawn());
	if (!enemy)
	{
		return false;
	}

	float distanceToPlayer = FVector::Dist(enemy->GetActorLocation(), player->GetActorLocation());

	FVGlobals::LogToScreen("Distance to the Player " + FString::SanitizeFloat(distanceToPlayer));

	return distanceToPlayer <= dection;
}
 