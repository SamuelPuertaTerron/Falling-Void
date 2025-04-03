// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTFindPlayerLocation.generated.h"

class AFVEnemyBase;
class AFVPlayerBase;
/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTFindPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UFVBTFindPlayerLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flank")
	bool CanFlank{ false };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flank")
	float FlankRadius{ 150.0f };

	UPROPERTY(EditAnywhere, Category = "Condition")
	FBlackboardKeySelector AttackRangeKey;
	UPROPERTY(EditAnywhere, Category = "Condition")
	FBlackboardKeySelector PlayerKey;
	UPROPERTY(EditAnywhere, Category = "Condition")
	FBlackboardKeySelector WaitDuration;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", meta = (AllowPrivateAccess = "true"))
	float MoveRadius{ 150.0f };

	UPROPERTY(EditAnywhere, Category = "Range")
	bool IsRangedEnemy;
	UPROPERTY(EditAnywhere, Category = "Range")
	float RangeAmountModifier {5.0f};

private:
	void MoveToPlayer(UBehaviorTreeComponent& OwnerComp, const AFVPlayerBase* player, const AFVEnemyBase* enemy) const;
	void FlankPlayer(UBehaviorTreeComponent& OwnerComp, AFVPlayerBase* player, AFVEnemyBase* enemy);
};