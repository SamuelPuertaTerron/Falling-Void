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

	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if (!blackboard) 
	{
		return EBTNodeResult::Failed;
	}

	blackboard->SetValueAsObject(PlayerLocationKey.SelectedKeyName, closetPlayer);
	blackboard->SetValueAsVector(TargetLocationKey.SelectedKeyName, closetPlayer->GetActorLocation());

	return EBTNodeResult::Succeeded;
}

TArray<AFVPlayerBase*> UFVBTFindPlayerLocation::GetAllPlayers() const
{
	UWorld* world = GetWorld();
	if (!world)
	{
		return {};
	}

	TArray<AFVPlayerBase*> players;

	TArray<AActor*> playerControllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), playerControllers);

	if(playerControllers.IsEmpty())
	{
		return {};
	}

	for (AActor* actorController : playerControllers)
	{
		APlayerController* controller = Cast<APlayerController>(actorController);
		if (!controller) 
		{
			return {};
		}

		AFVPlayerBase* player = Cast<AFVPlayerBase>(controller->GetPawn());
		if (!player) 
		{
			return {};
		}

		players.Add(player);
	}

	return players;
}

AFVPlayerBase* UFVBTFindPlayerLocation::GetClosetPlayer(const AFVEnemyBase* enemy) const
{
	AFVPlayerBase* closetPlayer = nullptr;
	float minDistance = FLT_MAX;

	auto players = GetAllPlayers();
	if (players.IsEmpty())
	{
		return nullptr;
	}

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