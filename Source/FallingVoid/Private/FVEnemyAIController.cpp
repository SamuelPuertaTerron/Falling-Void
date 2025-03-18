// Copyright: Falling Void Studios


#include "FVEnemyAIController.h"

#include "FVGlobals.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "Perception/AIPerceptionComponent.h"

#include "Perception/AISenseConfig_Sight.h"


AFVEnemyAIController::AFVEnemyAIController(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFVEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AFVEnemyBase* const enemy = Cast<AFVEnemyBase>(InPawn))
	{
		if (UBehaviorTree* const tree = enemy->GetBehaviorTree())
		{
			UBlackboardComponent* blackboard;
			UseBlackboard(tree->BlackboardAsset, blackboard);
			Blackboard = blackboard;
			RunBehaviorTree(tree);
		}
	}
}

void AFVEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AFVPlayerBase* PlayerActor = Cast<AFVPlayerBase>(GetBlackboardComponent()->GetValueAsObject("Player"));
	if (PlayerActor)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Updating Player Position"));
		// Update the player's location in the blackboard
		GetBlackboardComponent()->SetValueAsVector("TargetLocation", PlayerActor->GetActorLocation());
	}
}
