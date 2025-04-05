// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTEndRetreat.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTEndRetreat : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTEndRetreat();

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector RetreatKey;
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
