// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTMoveAwayFromPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTMoveAwayFromPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTMoveAwayFromPlayer();

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector PlayerKey;
	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector RetreatKey;

	UPROPERTY(EditAnywhere, Category = "Retreat")
	float RetreatDistance = { 400.0f };
	UPROPERTY(EditAnywhere, Category = "Retreat")
	float RetreatRandomness = { 300.0f }; 
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
