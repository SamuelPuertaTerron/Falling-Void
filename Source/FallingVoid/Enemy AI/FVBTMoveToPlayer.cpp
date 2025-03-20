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

    AFVEnemyBase* enemy = Cast<AFVEnemyBase>(AIController->GetPawn());
    if (!enemy)
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

    FVector targetLocation = Blackboard->GetValueAsVector(PlayerLocationKey.SelectedKeyName);
    AFVPlayerBase* player = Cast<AFVPlayerBase>(Blackboard->GetValueAsObject(PlayerKey.SelectedKeyName));

    if (!player)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (IsRangedEnemy)
    {
        float Distance = FVector::Dist(enemy->GetActorLocation(), player->GetActorLocation());

        if (Distance > enemy->AttackRange)
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
        Blackboard->SetValueAsVector(PlayerLocationKey.SelectedKeyName, targetLocation);
    }

    // Move the enemy toward the target location
    EPathFollowingRequestResult::Type MoveResult = AIController->MoveToLocation(targetLocation, AcceptanceRadius);

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
