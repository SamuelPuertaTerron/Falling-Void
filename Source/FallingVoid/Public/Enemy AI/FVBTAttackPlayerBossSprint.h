// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTAttackPlayerBossSprint.generated.h"

/**
 * The boss will attack the player at distance, ie 1500 unreal units
 */
UCLASS()
class FALLINGVOID_API UFVBTAttackPlayerBossSprint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UFVBTAttackPlayerBossSprint();
	~UFVBTAttackPlayerBossSprint() = default;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
