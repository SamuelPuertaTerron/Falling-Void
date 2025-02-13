// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
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

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	class UAISenseConfig_Sight* SightConfig;

	void SetupPerception();

	UFUNCTION()
	void OnTargetSpotted(AActor* actor, const FAIStimulus stimulus);
};
