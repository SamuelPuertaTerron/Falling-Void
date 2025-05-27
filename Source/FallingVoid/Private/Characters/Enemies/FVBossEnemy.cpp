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

	OnAttackBegin();

	UE_LOG(LogTemp, Error, TEXT("Attacking Player"));

    //OnAttackPlayer();
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

		controller->SetIsDead(IsDead);

		OnDied();
	}
}

void AFVBossEnemy::ResetCollision()
{
    IsComboAAttacking = false;
    IsComboBAttacking = false;
    IsComboCAttacking = false;

	if (CollisionComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Collision Component has not been set in the inspector"));
		return;
	}

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UE_LOG(LogTemp, Error, TEXT("Reset Collision"));
}