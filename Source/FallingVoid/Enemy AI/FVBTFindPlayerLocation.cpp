// Copyright: Falling Void Studios


#include "FVBTFindPlayerLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UFVBTFindPlayerLocation::UFVBTFindPlayerLocation()
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFVBTFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		//Get player location
		const FVector playerLocation = player->GetActorLocation();
		if (SearchRandom)
		{
			FNavLocation navLocation;

			//Get the navigation system and generate a random search area  around the player
			if(const auto * nav = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				if (nav->GetRandomPointInNavigableRadius(playerLocation, SearchRadius, navLocation))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), navLocation.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerLocation);

			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
