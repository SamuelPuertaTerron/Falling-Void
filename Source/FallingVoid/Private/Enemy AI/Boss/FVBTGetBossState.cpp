// Copyright: Falling Void Studios


#include "Enemy AI/Boss/FVBTGetBossState.h"

#include "FVEnemyAIController.h"
#include "Characters/Enemies/FVBossEnemy.h"


bool UFVBTGetBossState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(OwnerComp.GetAIOwner());
	if (!controller)
	{
		return false;
	}

	AFVBossEnemy* enemy = Cast<AFVBossEnemy>(controller->GetPawn());
	if (!enemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Found Boos"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Boos"));
	return ToggleInverse ? enemy->BossState != BossState : enemy->BossState == BossState;
}