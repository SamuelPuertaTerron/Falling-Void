// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "FVBTUpdatePlayerLocationService.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTUpdatePlayerLocationService : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTUpdatePlayerLocationService();

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

    // The Blackboard key for the player reference.
    UPROPERTY(EditAnywhere, Category = "Service")
    FBlackboardKeySelector PlayerKey;

    // The Blackboard key for the detection range.
    UPROPERTY(EditAnywhere, Category = "Service")
    FBlackboardKeySelector DetectionRangeKey;
};
