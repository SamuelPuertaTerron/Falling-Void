// Copyright: Falling Void Studios


#include "Enemy AI/FVBTFindPlayerLocation.h"

#include "FVEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "Kismet/GameplayStatics.h"

UFVBTFindPlayerLocation::UFVBTFindPlayerLocation()
{
	NodeName = "Find Player Location";
}

EBTNodeResult::Type UFVBTFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(OwnerComp.GetAIOwner());
	if (!controller)
	{
		return EBTNodeResult::Failed;
	}

	AFVEnemyBase* enemy = Cast<AFVEnemyBase>(controller->GetPawn());
	if (!enemy)
	{
		return EBTNodeResult::Failed;
	}

	AFVPlayerBase* closetPlayer = GetClosetPlayer(enemy);
	if (!closetPlayer)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerLocationKey.SelectedKeyName, closetPlayer);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, closetPlayer->GetActorLocation());

	return EBTNodeResult::Succeeded;
}

TArray<AFVPlayerBase*> UFVBTFindPlayerLocation::GetAllPlayers() const
{
	TArray<AFVPlayerBase*> players;

	TArray<AActor*> playerControllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), playerControllers);

	for (AActor* actorController : playerControllers)
	{
		APlayerController* controller = Cast<APlayerController>(actorController);
		if (!controller) 
		{
			return players;
		}

		AFVPlayerBase* player = Cast<AFVPlayerBase>(controller->GetPawn());
		if (!player) 
		{
			return players;
		}

		players.Add(player);
	}

	return players;
}

AFVPlayerBase* UFVBTFindPlayerLocation::GetClosetPlayer(const AFVEnemyBase* enemy) const
{
	AFVPlayerBase* closetPlayer = nullptr;
	float minDistance = FLT_MAX;

	static auto players = GetAllPlayers(); // Lazy load as in theory no player could join through the game.

	for (AFVPlayerBase* player : players)
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