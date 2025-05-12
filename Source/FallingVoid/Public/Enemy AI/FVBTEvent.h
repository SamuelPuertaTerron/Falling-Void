// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTEvent.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTEvent : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UFVBTEvent();
	~UFVBTEvent() = default;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
