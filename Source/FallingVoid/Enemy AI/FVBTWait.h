// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTWait.generated.h"

UE_DEPRECATED_MACRO("5.3", "This is deprecated for ")

/**
 *  Custom wait to implement the enemy attack time
 */
UCLASS()
class FALLINGVOID_API UFVBTWait : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTWait();

	UPROPERTY(EditAnywhere, Category = "Wait")
	FBlackboardKeySelector WaitDurationKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float m_RemainingWaitTime;
};
