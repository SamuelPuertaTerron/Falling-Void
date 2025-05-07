// Copyright: Falling Void Studios


#include "Characters/Enemies/FVHunterEnemy.h"

#include "FVEnemyAIController.h"
#include "Characters/FVPlayerBase.h"

static FString GetCurrentStateAsString(const EPlayerHealthState& state)
{
	switch (state)
	{
	case EPlayerHealthState::None:
		return "None";
	case EPlayerHealthState::Alive:
		return "Alive";
	case EPlayerHealthState::Downed:
		return "Downed";
	case EPlayerHealthState::Dead:
		return "Dead";
	default:
		return "NULL";
	}

	return "NULL";
}

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

	UE_LOG(LogTemp, Warning, TEXT("Player State: %s"), *GetCurrentStateAsString(playerBase->PlayerHealthState));

	OnAttackPlayer();

	GetWorldTimerManager().SetTimer(m_TimeHandle, [this, playerBase, currentState]()
		{
			if (playerBase && playerBase->IsValidLowLevel())
			{
				playerBase->PlayerHealthState = currentState;
			}
		}, AttackTime, false);
}
