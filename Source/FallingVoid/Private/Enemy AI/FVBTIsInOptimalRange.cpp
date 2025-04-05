// Copyright: Falling Void Studios


#include "Enemy AI/FVBTIsInOptimalRange.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "FVEnemyAIController.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "Kismet/GameplayStatics.h"

UFVBTIsInOptimalRange::UFVBTIsInOptimalRange()
{
	NodeName = "Is In Optimal Range";
}

bool UFVBTIsInOptimalRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(OwnerComp.GetAIOwner());
	if (!controller)
	{
		return false;
	}

	AFVEnemyBase* enemy = Cast<AFVEnemyBase>(controller->GetPawn());
	if (!enemy)
	{
		return false;
	}


	AFVPlayerBase* closetPlayer = GetClosetPlayer(enemy);
	if (!closetPlayer)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerKey.SelectedKeyName, closetPlayer);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, closetPlayer->GetActorLocation());

	FVector enemyLocation = enemy->GetActorLocation();
	FVector playerLocation = closetPlayer->GetActorLocation();

	// Calculate distance with validation
	float distance = FVector::Distance(playerLocation, enemyLocation);
	if (!FMath::IsFinite(distance))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid distance calculation: %f"), distance);
		return false;
	}

	// Final range check
	bool isInRange = (distance >= MinRange) && (distance <= MaxRange);

	UE_LOG(LogTemp, Warning, TEXT("Distance: %.2f, Range: [%.2f-%.2f], InRange: %d"),
		distance, MinRange, MaxRange, isInRange);

	return isInRange;
}

TArray<AFVPlayerBase*> UFVBTIsInOptimalRange::GetAllPlayers() const
{
	TArray<AFVPlayerBase*> players;

	TArray<AActor*> playerControllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), playerControllers);

	for (AActor* actorController : playerControllers)
	{
		APlayerController* controller = Cast<APlayerController>(actorController);
		if (controller && controller->GetPawn())
		{
			AFVPlayerBase* player = Cast<AFVPlayerBase>(controller->GetPawn());
			players.Add(player);
		}
	}

	return players;
}

AFVPlayerBase* UFVBTIsInOptimalRange::GetClosetPlayer(const AFVEnemyBase* enemy) const
{
	AFVPlayerBase* closetPlayer = nullptr;
	float minDistance = FLT_MAX;


	for (AFVPlayerBase* player : GetAllPlayers())
	{
		if (!player || player->GetIsDeadOrDowned())
		{
			continue;
		}

		float distance = FVector::Distance(enemy->GetActorLocation(), player->GetActorLocation());

		if (distance < minDistance)
		{
			minDistance = distance;
			closetPlayer = player;
		}
	}

	return closetPlayer;
}
