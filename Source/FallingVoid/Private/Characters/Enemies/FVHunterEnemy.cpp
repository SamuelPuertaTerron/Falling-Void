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

void AFVHunterEnemy::Stun(float delay)
{
	if (!m_pController || !IsValid(m_pController))
	{
		UE_LOG(LogTemp, Error, TEXT("Controller is null or invalid!"));
		return;
	}

	m_pController->SetIsStunned(true);
	m_pController->StopMovement();

	OnStunStart();
	
	AFVEnemyAIController* controller = m_pController;
	TWeakObjectPtr<AFVEnemyBase> thisWeak = this;
	GetWorldTimerManager().SetTimer(m_SunTimer, [thisWeak, controller]()
		{
			if (thisWeak.IsValid() && controller && IsValid(controller))
			{
				controller->SetIsStunned(false);
				auto player = controller->GetClosetPlayer();
				if (!player || IsValid(player)) 
				{
					UE_LOG(LogTemp, Error, TEXT("Closet Player is null or invalid!"));
					thisWeak->OnStunEnd();
					return;
				}

				player->PlayerHealthState = EPlayerHealthState::Alive;
				thisWeak->OnStunEnd();
			}
		}, delay, false);
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
	if (!playerBase || playerBase->GetIsDeadOrDowned())
	{
		UE_LOG(LogTemp, Error, TEXT("Player is null"))
		return;
	}

	IsPlayerPinned = false;
	playerBase->PlayerHealthState = EPlayerHealthState::Alive;
	UE_LOG(LogTemp, Warning, TEXT("Player Unpinned: %s"), *GetCurrentStateAsString(playerBase->PlayerHealthState));
}
