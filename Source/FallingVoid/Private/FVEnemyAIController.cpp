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
	SetupPerception();
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

void AFVEnemyAIController::SetupPerception()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	if (AFVEnemyBase* const owner = Cast<AFVEnemyBase>(GetPawn()))
	{
		
	}

	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 500.0f;
		SightConfig->LoseSightRadius = 25.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->SetMaxAge(5.0f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AFVEnemyAIController::OnTargetSpotted);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void AFVEnemyAIController::OnTargetSpotted(AActor* actor, const FAIStimulus stimulus)
{
	if (const AFVPlayerBase* player = Cast<AFVPlayerBase>(actor))
	{
		GetBlackboardComponent()->SetValueAsBool("SpottedPlayer", stimulus.WasSuccessfullySensed());
		FVGlobals::LogToScreen("Has Spotted Player");
	}
}
