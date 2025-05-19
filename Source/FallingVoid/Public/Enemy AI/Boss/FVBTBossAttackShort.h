// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTBossAttackShort.generated.h"

/**
 * 
 */
UCLASS()
class UFVBTBossAttackShort : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTBossAttackShort();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector LastAttackTIme;
	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector PlayerKey;
};
