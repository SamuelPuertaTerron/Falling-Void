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
    /*AAIController* aiController = OwnerComp.GetAIOwner();
    if (!aiController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    AFVEnemyBase* enemy = Cast<AFVEnemyBase>(aiController->GetPawn());
    if (!enemy)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // Get the player's location from the Blackboard
    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
    if (!blackboard)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (!blackboard->GetValueAsBool("CanMove"))
    {
        enemy->StopMovement();
        UE_LOG(LogTemp, Warning, TEXT("Blackboard State FALSE"))
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    FVector targetLocation = blackboard->GetValueAsVector(PlayerLocationKey.SelectedKeyName);
    AFVPlayerBase* player = Cast<AFVPlayerBase>(blackboard->GetValueAsObject(PlayerKey.SelectedKeyName));

    if (!player)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (IsRangedEnemy)
    {
        float distance = FVector::Dist(enemy->GetActorLocation(), player->GetActorLocation());

        if (distance > enemy->AttackRange)
        {
            targetLocation = player->GetActorLocation();
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetLocation);
        }
        else
        {
            // Calculate the new target position behind the attack range
            FVector direction = (enemy->GetActorLocation() - player->GetActorLocation()).GetSafeNormal();
            targetLocation = player->GetActorLocation() + (direction * enemy->AttackRange);

            // Set the player's location in the blackboard
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetLocation);
        }
    }
    else
    {
        // Update the target location to the player's current location for the melee enemy only
        targetLocation = player->GetActorLocation();
        blackboard->SetValueAsVector(PlayerLocationKey.SelectedKeyName, targetLocation);
    }*/

    AAIController* aiController = OwnerComp.GetAIOwner();
    if (!aiController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // Get the player's location from the Blackboard
    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
    if (!blackboard)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // Move the enemy toward the target location
    EPathFollowingRequestResult::Type moveResult = aiController->MoveToLocation(blackboard->GetValueAsVector(PlayerLocationKey.SelectedKeyName), AcceptanceRadius);

	switch (moveResult)
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
