// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "FVBTIsEnemyStunned.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTIsEnemyStunned : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTIsEnemyStunned();
	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector IsStunnedKey;
private:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
