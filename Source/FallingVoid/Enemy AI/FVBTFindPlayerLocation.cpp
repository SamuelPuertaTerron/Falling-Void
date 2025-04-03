// Copyright: Falling Void Studios

#include "FVBTFindPlayerLocation.h"

#include "FVGlobals.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "SpawnSystem/FVSpawnManagerSubsystem.h"

UFVBTFindPlayerLocation::UFVBTFindPlayerLocation()
{
	NodeName = TEXT("Find Player Location");
	bNotifyTick = true; // Enable ticking for this task
}

EBTNodeResult::Type UFVBTFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
	return EBTNodeResult::InProgress;
}

void UFVBTFindPlayerLocation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Get the AI controller and its pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool("CanMove"))
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

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AttackRangeKey.SelectedKeyName, enemy->AttackRange);
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitDuration.SelectedKeyName, enemy->AttackTime);

	AFVPlayerBase* player = Cast<AFVPlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName));
	if (!player)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (!CanFlank)
	{
		MoveToPlayer(OwnerComp, player, enemy);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	AFVSpawnManager* manager = GetWorld()->GetGameInstance()->GetSubsystem<UFVSpawnManagerSubsystem>()->GetSpawnManager();
	if (!manager)
	{
		LOG("AFVSpawnManager is null!");
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	int maxEnemiesInRound = manager->GetMaxEnemiesThisWave();
	int maxEnemiesToFlank = maxEnemiesInRound / 2;

	if (manager->EnemiesRemaining <= maxEnemiesToFlank)
	{
		FlankPlayer(OwnerComp, player, enemy);
	}
	else
	{
		MoveToPlayer(OwnerComp, player, enemy);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Moving To Player with his location being %s"), *targetLocation.ToString());
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

void UFVBTFindPlayerLocation::MoveToPlayer(UBehaviorTreeComponent& OwnerComp, const AFVPlayerBase* player, const AFVEnemyBase* enemy) const
{
	FVector targetLocation = player->GetActorLocation();
	targetLocation += FMath::VRand() * (MoveRadius * 0.2f);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetLocation);

	LOG("Moving to Player");
}

void UFVBTFindPlayerLocation::FlankPlayer(UBehaviorTreeComponent& OwnerComp, AFVPlayerBase* player, AFVEnemyBase* enemy)
{
	//Player Position
	FVector playerLocation = player->GetActorLocation();
	FVector playerForward = player->GetActorForwardVector();
	FVector playerRight = player->GetActorRightVector();

	// Calculate positions to left and right of player
	FVector leftFlankPos = playerLocation + (playerRight * -FlankRadius) + (playerForward * FlankRadius);
	FVector rightFlankPos = playerLocation + (playerRight * FlankRadius) + (playerForward * FlankRadius);

	float distToLeft = FVector::Dist(enemy->GetActorLocation(), leftFlankPos);
	float distToRight = FVector::Dist(enemy->GetActorLocation(), rightFlankPos);

	FVector targetFlankPos = distToLeft > distToRight ? leftFlankPos : rightFlankPos;

	//Add some randomness
	targetFlankPos += FMath::VRand() * (FlankRadius * 0.3f);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetFlankPos);

	LOG("Flanking");
}
