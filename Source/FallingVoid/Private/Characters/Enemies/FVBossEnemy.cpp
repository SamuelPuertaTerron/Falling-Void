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

	if (!IsDead)
	{
		return;
	}

    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    OnAttackPlayer();
}

void AFVBossEnemy::TakeDamage(float damage)
{
	Health -= damage;
	OnTakenDamage();
	if (Health <= 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("Died!"));
		IsDead = true;

		AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(GetController());
		if (!controller)
		{
			return;
		}

		controller->SetIsDead(IsDead);

		OnDied();
	}

	UE_LOG(LogTemp, Error, TEXT("Taken Damage!"));
}

void AFVBossEnemy::ResetCollision()
{
    IsComboAAttacking = false;
    IsComboBAttacking = false;
    IsComboCAttacking = false;

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorldTimerManager().ClearTimer(m_TimerHandler);
}