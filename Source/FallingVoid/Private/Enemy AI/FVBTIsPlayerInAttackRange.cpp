// Copyright: Falling Void Studios


#include "Enemy AI/FVBTIsPlayerInAttackRange.h"

#include "FVEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
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

	FVector playerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetLocationKey.SelectedKeyName);
	FVector enemyLocation = enemy->GetActorLocation();

	float attackRange = enemy->AttackRange;
	float distance = FVector::Distance(playerLocation, enemyLocation);

	bool isInRange = distance <= attackRange;
	UE_LOG(LogTemp, Warning, TEXT("In Range: %d"), isInRange);

	return isInRange;
}
