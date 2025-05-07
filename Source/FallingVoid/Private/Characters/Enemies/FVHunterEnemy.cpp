// Copyright: Falling Void Studios


#include "Characters/Enemies/FVHunterEnemy.h"

#include "FVEnemyAIController.h"
#include "Characters/FVPlayerBase.h"

void AFVHunterEnemy::Attack()
{
	AFVEnemyAIController* enemyController = Cast<AFVEnemyAIController>(GetController());
	if (!enemyController)
	{
		UE_LOG(LogTemp, Error, TEXT(""))
		return;
	}
	AFVPlayerBase* playerBase = enemyController->GetClosetPlayer();
	if (!playerBase)
	{
		return;
	}

	auto currentState = playerBase->PlayerHealthState;
	playerBase->PlayerHealthState = EPlayerHealthState::Pinned;

	OnAttackPlayer();

	GetWorldTimerManager().SetTimer(m_TimeHandle, [this, playerBase, currentState]()
		{
			if (playerBase && playerBase->IsValidLowLevel())
			{
				playerBase->PlayerHealthState = currentState;
			}
		}, AttackTime, false); // Added 'false' for one-shot timer
}
