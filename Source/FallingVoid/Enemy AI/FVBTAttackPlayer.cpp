// Copyright: Falling Void Studios


#include "FVBTAttackPlayer.h"

#include "Characters/Enemies/FVEnemyBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UFVBTAttackPlayer::UFVBTAttackPlayer()
{
	NodeName = TEXT("Attack Player");
}

EBTNodeResult::Type UFVBTAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* aiController = OwnerComp.GetAIOwner();
	if (!aiController) 
		return EBTNodeResult::Failed;

	AFVEnemyBase* enemy = Cast<AFVEnemyBase>(aiController->GetPawn());
	if (!enemy)
		return EBTNodeResult::Failed;

	AFVBaseCharacter* player = Cast<AFVBaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (!player)
		return EBTNodeResult::Failed;

	//Look at player
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(enemy->GetActorLocation(), player->GetActorLocation());
	enemy->SetActorRotation(LookAtRotation);

	//Attack if the distance between this enemy and the player is less than the attack range
	if (FVector::Dist(enemy->GetActorLocation(), player->GetActorLocation()) < enemy->AttackRange)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitDurationKey.SelectedKeyName, enemy->AttackTime);

		UE_LOG(LogTemp, Warning, TEXT("Attacked Player: %s"), *player->GetName());
		enemy->Attack();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	DrawDebugSphere(GetWorld(), enemy->GetActorLocation(), enemy->AttackRange, 12, FColor::Red, false, 2.0f);

	return EBTNodeResult::Failed;
}
