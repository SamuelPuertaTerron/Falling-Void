// Copyright: Falling Void Studios


#include "FVBTAttackPlayer.h"

#include "Characters/Enemies/FVEnemyBase.h"
#include "Characters/FVPlayerBase.h"
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

	AFVPlayerBase* player = Cast<AFVPlayerBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (!player)
		return EBTNodeResult::Failed;

	if (player->GetIsDeadOrDowned())
		return EBTNodeResult::Failed;

	//Look at player
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(enemy->GetActorLocation(), player->GetActorLocation());
	enemy->SetActorRotation(LookAtRotation);

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AttackTimeKey.SelectedKeyName, enemy->AttackTime);

	DrawDebugSphere(GetWorld(), enemy->GetActorLocation(), enemy->AttackRange, 12, FColor::Red, false, 2.0f);

	UE_LOG(LogTemp, Warning, TEXT("Attacked Player: %s"), *player->GetName());
	enemy->Attack();
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
