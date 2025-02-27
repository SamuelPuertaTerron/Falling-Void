// Copyright: Falling Void Studios


#include "FVBTUpdatePlayerLocationService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/FVBaseCharacter.h"
#include "Characters/Enemies/FVEnemyBase.h"

UFVBTUpdatePlayerLocationService::UFVBTUpdatePlayerLocationService()
{
	NodeName = TEXT("Update Player Location");
	bNotifyTick = true;
}

void UFVBTUpdatePlayerLocationService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AFVBaseCharacter* player = Cast<AFVBaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName));
	if (!player)
	{
		return;
	}

	float detectionRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(DetectionRangeKey.SelectedKeyName);

	AAIController* controller = OwnerComp.GetAIOwner();
	if (controller)
	{
		return;
	}

	AFVEnemyBase* enemy = Cast<AFVEnemyBase>(controller->GetPawn());
	if (!enemy)
	{
		return;
	}

	float distanceToPlayer = FVector::Dist(enemy->GetActorLocation(), player->GetActorLocation());

	if (distanceToPlayer <= distanceToPlayer)
	{
		//Set the player key if the player is in range
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerKey.SelectedKeyName, player);
	}
	else
	{
		//Player out of range so clear the player value from the blackboard
		OwnerComp.GetBlackboardComponent()->ClearValue(PlayerKey.SelectedKeyName);
	}
}
