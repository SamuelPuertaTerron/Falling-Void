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
	UFVBTFindPlayerLocation();

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector TargetLocationKey;
	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector PlayerLocationKey;
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	TArray<AFVPlayerBase*> GetAllPlayers() const;

	AFVPlayerBase* GetClosetPlayer(const AFVEnemyBase* enemy) const;
};
