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

void AFVEnemyAIController::SetIsStunned(bool value)
{
    UBlackboardComponent* blackboardComp = GetBlackboardComponent();
    if (blackboardComp)
    {
        FBlackboard::FKey KeyID = blackboardComp->GetKeyID("IsStunned");
        if (KeyID != FBlackboard::InvalidKey)
        {
            blackboardComp->SetValueAsBool("IsStunned", value);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("IsStunned key not found in Blackboard!"));
        }
    }
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

    // Get the enemy location
    AFVEnemyBase* enemy = Cast<AFVEnemyBase>(GetPawn());
    FVector enemyLocation = enemy->GetActorLocation();

    float closestDistance = FLT_MAX; // Correctly initialize


    // Get the world safely
    UWorld* world = GetWorld();
    if (!world)
    {
        return;
    }

    // Iterate over all player controllers
    for (FConstPlayerControllerIterator iterator = world->GetPlayerControllerIterator(); iterator; ++iterator)
    {
        APlayerController* controller = iterator->Get();
        if (!controller) continue;

        AFVPlayerBase* playerCharacter = Cast<AFVPlayerBase>(controller->GetPawn());
        if (!playerCharacter)
            continue;

        if (playerCharacter->GetIsDeadOrDowned())
        {
            continue;
        }

         float Distance = FVector::Dist(enemyLocation, playerCharacter->GetActorLocation());

        // Check if this player is closer
        if (Distance < closestDistance)
        {
            //UE_LOG(LogTemp, Warning, TEXT("Found Closet Player with name %s"), *PlayerCharacter->GetName());
            closestDistance = Distance;
            GetBlackboardComponent()->SetValueAsObject("Player", playerCharacter);
        }
    }

}
