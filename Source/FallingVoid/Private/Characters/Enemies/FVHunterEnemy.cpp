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
	case EPlayerHealthState::Pinned:
		return "Pinned";
	default:
		return "NULL";
	}
}

void AFVHunterEnemy::Attack()
{
	if (IsPlayerPinned)
	{
		return;
	}

	AFVEnemyAIController* enemyController = Cast<AFVEnemyAIController>(GetController());
	if (!enemyController)
	{
		UE_LOG(LogTemp, Error, TEXT(""))
		return;
	}
	AFVPlayerBase* playerBase = enemyController->GetClosetPlayer();
	if (!playerBase || !playerBase->GetIsAlive())
	{
		return;
	}

	playerBase->PlayerHealthState = EPlayerHealthState::Pinned;
	IsPlayerPinned = true;
	UE_LOG(LogTemp, Warning, TEXT("Player State: %s"), *GetCurrentStateAsString(playerBase->PlayerHealthState));

	OnAttackPlayer();
}

void AFVHunterEnemy::TakeDamage(float damage)
{
	Super::TakeDamage(damage);
}

void AFVHunterEnemy::SetPlayerAlive()
{
	AFVEnemyAIController* enemyController = Cast<AFVEnemyAIController>(GetController());
	if (!enemyController)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy Controller is null"))
		return;
	}
	AFVPlayerBase* playerBase = enemyController->GetClosetPlayer();
	if (!playerBase)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is null"))
		return;
	}

	IsPlayerPinned = false;
	playerBase->PlayerHealthState = EPlayerHealthState::Alive;
	UE_LOG(LogTemp, Warning, TEXT("Player Unpinned: %s"), *GetCurrentStateAsString(playerBase->PlayerHealthState));
}
