// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "FVBTRandom.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTRandom : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	/* The chance of this being true, default is 0.3 or 30%. */
	UPROPERTY(EditAnywhere, Category = "Random")
	float Chance = { 0.3f };

private:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
