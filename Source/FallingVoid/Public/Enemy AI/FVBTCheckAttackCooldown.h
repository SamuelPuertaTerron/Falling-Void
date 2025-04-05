// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "FVBTCheckAttackCooldown.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTCheckAttackCooldown : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTCheckAttackCooldown();

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector LastAttackTIme;
private:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
