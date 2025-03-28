// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "FVEnemyAIController.generated.h"

class FObjectInitializer;
/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit AFVEnemyAIController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "Condition")
	FBlackboardKeySelector PlayerKey;

	/* Functions that might be used multiple times */

	/** Sets the can move key to the blackboard if it exist */
	void SetCanMoveBlackboard(bool value);

protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;
private:
};
