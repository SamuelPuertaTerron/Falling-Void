// Copyright: Falling Void Studios


#include "FVBTMoveToPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "Navigation/PathFollowingComponent.h"

UFVBTMoveToPlayer::UFVBTMoveToPlayer()
{
	NodeName = "Move To Player";
	bNotifyTick = true;
}

EBTNodeResult::Type UFVBTMoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MoveToPlayer(OwnerComp);

	return EBTNodeResult::InProgress;
}

void UFVBTMoveToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	MoveToPlayer(OwnerComp);
}

void UFVBTMoveToPlayer::MoveToPlayer(UBehaviorTreeComponent& OwnerComp)
{
    // Get the AI controller
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // Get the player's location from the Blackboard
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    FVector TargetLocation = Blackboard->GetValueAsVector(PlayerLocationKey.SelectedKeyName);
    AFVPlayerBase* Player = Cast<AFVPlayerBase>(Blackboard->GetValueAsObject(PlayerKey.SelectedKeyName));

    if (!Player)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // Update the target location to the player's current location
    TargetLocation = Player->GetActorLocation();
    Blackboard->SetValueAsVector(PlayerLocationKey.SelectedKeyName, TargetLocation);

    // Move the enemy toward the target location
    EPathFollowingRequestResult::Type MoveResult = AIController->MoveToLocation(TargetLocation, AcceptanceRadius);

	switch (MoveResult)
    {
    case EPathFollowingRequestResult::Failed:
        UE_LOG(LogTemp, Warning, TEXT("MoveTo failed!"));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        break;
    case EPathFollowingRequestResult::AlreadyAtGoal:
        UE_LOG(LogTemp, Warning, TEXT("Already at goal!"));
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        break;
    case EPathFollowingRequestResult::RequestSuccessful:
        // Continue moving
        break;
    }
}
