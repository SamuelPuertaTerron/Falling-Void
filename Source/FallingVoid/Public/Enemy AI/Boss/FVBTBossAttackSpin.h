// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTBossAttackSpin.generated.h"

/**
 * Now that I think about this is the same as Short Attack just with a different set of animations
 */
UCLASS()
class FALLINGVOID_API UFVBTBossAttackSpin : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTBossAttackSpin();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
