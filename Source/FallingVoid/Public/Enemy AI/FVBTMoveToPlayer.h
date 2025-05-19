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

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector TargetLocationKey;

	UPROPERTY(EditAnywhere, Category = "Keys")
	float Radius = {150.0f};

	UPROPERTY(EditAnywhere, Category = "Random Movement")
	float MinRandomOffset = { 25.0f };
	UPROPERTY(EditAnywhere, Category = "Random Movement")
	float MaxRandomOffset = { 50.0f };

	UPROPERTY(EditAnywhere, Category = "Boss")
	bool IsBoss = { false };

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
