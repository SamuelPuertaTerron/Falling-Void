// Copyright: Falling Void Studios


#include "FVBTFindRandomLocation.h"

#include "FVEnemyAIController.h"
#include "NavigationSystem.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UFVBTFindRandomLocation::UFVBTFindRandomLocation(const FObjectInitializer& FObjectInitializer)
{
	NodeName = "Find Random Location";
}

EBTNodeResult::Type UFVBTFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Attempt to get the enemy AI Controller
	if (const AFVEnemyAIController* enemyAI = Cast<AFVEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		if (const auto* enemy = enemyAI->GetPawn())
		{
			const FVector location = enemy->GetActorLocation();

			if (const auto* nav = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				//Attempts to find a random point in the nav mesh
				FNavLocation navLocation;
				if (nav->GetRandomPointInNavigableRadius(location, SearchRadius, navLocation))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), navLocation.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
