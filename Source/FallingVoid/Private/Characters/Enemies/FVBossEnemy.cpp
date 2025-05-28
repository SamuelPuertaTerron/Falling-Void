// Copyright: Falling Void Studios


#include "Characters/Enemies/FVBossEnemy.h"

#include "FVEnemyAIController.h"
#include "Components/CapsuleComponent.h"


void AFVBossEnemy::Stun(float delay)
{
	//Boss Enemy cannot be stunned
}

void AFVBossEnemy::Attack()
{
    if (CollisionComponent == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Collision Component has not been set in the inspector"));
        return;
    }

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	UE_LOG(LogTemp, Error, TEXT("Attacking Player"));

    OnAttackPlayer();
}

void AFVBossEnemy::TakeDamage(float damage)
{
	Health -= damage;
	OnTakenDamage();
	if (Health <= 0.0f)
	{
		IsDead = true;

		AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(GetController());
		if (!controller)
		{
			return;
		}

		BossState = EBossState::Dead;
		controller->SetIsDead(IsDead);

		OnDied();
	}
}

void AFVBossEnemy::ResetCollision()
{
	if (CollisionComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Collision Component has not been set in the inspector"));
		return;
	}

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UE_LOG(LogTemp, Error, TEXT("Reset Collision"));

	if (BossState == EBossState::Jumping || BossState == EBossState::None)
	{
		return;
	}

	BossState = EBossState::Moving;
}