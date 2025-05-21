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
    if (!IsValid(this))
    {
        UE_LOG(LogTemp, Error, TEXT("Controller is not valid!"));
        return;
    }

    UBlackboardComponent* blackboardComp = GetBlackboardComponent();
    if (!blackboardComp)
    {
        UE_LOG(LogTemp, Error, TEXT("Blackboard component is null!"));
        return;
    }

    FBlackboard::FKey KeyID = blackboardComp->GetKeyID("IsStunned");
    if (KeyID == FBlackboard::InvalidKey)
    {
        UE_LOG(LogTemp, Error, TEXT("IsStunned key not found in Blackboard!"));
        return;
    }

    blackboardComp->SetValueAsBool("IsStunned", value);
    UE_LOG(LogTemp, Warning, TEXT("Called SetIsStunned: %d"), value);
}

void AFVEnemyAIController::SetIsDead(bool value)
{
    if (!IsValid(this))
    {
        UE_LOG(LogTemp, Error, TEXT("Controller is not valid!"));
        return;
    }

    UBlackboardComponent* blackboardComp = GetBlackboardComponent();
    if (!blackboardComp)
    {
        UE_LOG(LogTemp, Error, TEXT("Blackboard component is null!"));
        return;
    }

    FBlackboard::FKey KeyID = blackboardComp->GetKeyID("IsStunned");
    if (KeyID == FBlackboard::InvalidKey)
    {
        UE_LOG(LogTemp, Error, TEXT("IsStunned key not found in Blackboard!"));
        return;
    }

    blackboardComp->SetValueAsBool("IsDead", value);
}

AFVPlayerBase* AFVEnemyAIController::GetClosetPlayer() const
{
    auto player = Cast<AFVPlayerBase>(GetBlackboardComponent()->GetValueAsObject("Player"));
    if (!player)
    {
        UE_LOG(LogTemp, Error, TEXT("Player is null from the blackboard"));
        return nullptr;
    }

    return player;
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
    if(!enemy)
    {
        //UE_LOG(LogTemp, Error, TEXT("Enemy is null"))
        return;
    }
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
