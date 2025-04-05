// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FVBTMaintainDistanceFromPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API UFVBTMaintainDistanceFromPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFVBTMaintainDistanceFromPlayer();
};
