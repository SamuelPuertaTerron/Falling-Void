// Copyright: Falling Void Studios


#include "Enemy AI/FVBTRandom.h"

bool UFVBTRandom::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return FMath::FRand() <= Chance;
}
