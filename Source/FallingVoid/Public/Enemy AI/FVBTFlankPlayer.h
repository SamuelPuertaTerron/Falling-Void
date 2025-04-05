// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTFlankPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTFlankPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTFlankPlayer();

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector TargetLocationKey;

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector PlayerKey;

	UPROPERTY(EditAnywhere, Category = "Keys")
	float FlankRadius = {50.0f};
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
