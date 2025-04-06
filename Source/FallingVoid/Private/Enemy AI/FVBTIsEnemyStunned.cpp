// Copyright: Falling Void Studios


#include "Enemy AI/FVBTIsEnemyStunned.h"

#include "BehaviorTree/BlackboardComponent.h"

UFVBTIsEnemyStunned::UFVBTIsEnemyStunned()
{
	NodeName = "Is Stunned";
}

bool UFVBTIsEnemyStunned::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool isStunned = OwnerComp.GetBlackboardComponent()->GetValueAsBool(IsStunnedKey.SelectedKeyName);

	UE_LOG(LogTemp, Warning, TEXT("Is Stunned: %d"), isStunned);

	return isStunned;
}
