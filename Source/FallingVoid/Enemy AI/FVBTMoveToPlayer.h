// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTMoveToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTMoveToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
    UFVBTMoveToPlayer();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
    // Key for the player's location in the Blackboard
    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector PlayerLocationKey;

    // Key for the player's reference in the Blackboard
    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector PlayerKey;

    // Acceptance radius for the MoveTo operation
    UPROPERTY(EditAnywhere, Category = "Range")
    bool IsRangedEnemy = { false };

    // Acceptance radius for the MoveTo operation
    UPROPERTY(EditAnywhere, Category = "Movement")
    float AcceptanceRadius = { 50.0f };

private:
    // Helper function to move the enemy toward the target location
    void MoveToPlayer(UBehaviorTreeComponent& OwnerComp);
};
