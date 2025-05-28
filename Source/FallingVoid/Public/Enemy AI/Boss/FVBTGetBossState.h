// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "FVBTGetBossState.generated.h"

enum class EBossState : uint8;
/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTGetBossState : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "State")
	EBossState BossState;

	UPROPERTY(EditAnywhere, Category = "State")
	bool ToggleInverse{ false };
};
