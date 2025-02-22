// Copyright: Falling Void Studios


#include "FVBTFindPlayerLocation.h"

#include "FVGlobals.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Enemies/FVEnemyBase.h"

UFVBTFindPlayerLocation::UFVBTFindPlayerLocation()
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFVBTFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the enemy actor
	AFVEnemyBase* enemy = Cast<AFVEnemyBase>(OwnerComp.GetOwner());
	if (!enemy)
	{
		return EBTNodeResult::Failed;
	}

	//Get the enemy location
	FVector enemyLocation = enemy->GetActorLocation();

	//This will store the closet player that this enemy has found
	AFVPlayerBase* closetPlayer = nullptr;
	float closetDistance = 0;

	//Find the closet player
	for (FConstPlayerControllerIterator iterator = GetWorld()->GetPlayerControllerIterator(); iterator; ++iterator)
	{
		if (APlayerController* controller = iterator->Get())
		{
			if (AFVPlayerBase* playerCharacter = Cast<AFVPlayerBase>(controller->GetPawn()))
			{
				FVector playerLocation = playerCharacter->GetActorLocation();
				float distance = FVector::Dist(enemyLocation, playerLocation);

				//Check if this distance is closer than the prev distance
				if (distance < closetDistance)
				{
					closetDistance = distance;
					closetPlayer = playerCharacter;
					FVGlobals::LogToScreen("Closet Player with name: " + closetPlayer->GetName());
					UE_LOG(LogTemp, Warning, TEXT("Closet Player Found"))
				}
			}
		}
	}

	if (closetPlayer)
	{
		//If search random than random search around the known players location
		if (SearchRandom)
		{
			FNavLocation navLocation;

			//Get the navigation system and generate a random search area  around the player
			if(const auto * nav = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				if (nav->GetRandomPointInNavigableRadius(closetPlayer->GetActorLocation(), SearchRadius, navLocation))
				{
					//Set the player location in the blackboard
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), navLocation.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
		else
		{
			//Set the player location in the blackboard
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), closetPlayer->GetActorLocation());

			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
