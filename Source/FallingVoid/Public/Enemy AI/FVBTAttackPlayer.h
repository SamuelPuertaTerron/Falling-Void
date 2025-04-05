// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTAttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTAttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTAttackPlayer();


	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector LastAttackTIme;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
