// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTMoveToWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTMoveToWaypoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTMoveToWaypoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector CanAttackKey;

	UPROPERTY(EditAnywhere, Category = "Raduis")
	float Radius{ 50.0f };
};
