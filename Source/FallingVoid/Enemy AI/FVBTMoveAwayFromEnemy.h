// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTMoveAwayFromEnemy.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTMoveAwayFromEnemy : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UFVBTMoveAwayFromEnemy();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Condition")
	FBlackboardKeySelector PlayerKey;
	UPROPERTY(EditAnywhere, Category = "Condition")
	FBlackboardKeySelector TargetLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
	float MoveAwayRadiusMin{ 850.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
	float MoveAwayRadiusMax{ 2500.0f };
};
