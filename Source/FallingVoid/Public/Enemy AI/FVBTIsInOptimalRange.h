// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "FVBTIsInOptimalRange.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTIsInOptimalRange : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public :
	UFVBTIsInOptimalRange();

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector TargetLocationKey;
	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector PlayerKey;

	UPROPERTY(EditAnywhere, Category = "Keys")
	float MinRange = {500.0f};
	UPROPERTY(EditAnywhere, Category = "Keys")
	float MaxRange = {100.0f};
private:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	TArray<AFVPlayerBase*> GetAllPlayers() const;

	AFVPlayerBase* GetClosetPlayer(const AFVEnemyBase* enemy) const;
};
