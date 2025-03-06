// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "FVBTIsPlayerInRange.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTIsPlayerInRange : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTIsPlayerInRange();

	UPROPERTY(EditAnywhere, Category = "Condition")
	FBlackboardKeySelector PlayerKey;
	UPROPERTY(EditAnywhere, Category = "Condition")
	FBlackboardKeySelector AttackRangeKey;

	UPROPERTY(EditAnywhere, Category = "Range")
	bool IsRangedEnemy;
	UPROPERTY(EditAnywhere, Category = "Range")
	float RangeAmountModifier{ 5.0f };

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
