// Copyright: Falling Void Studios


#include "Characters/Enemies/FVBossEnemy.h"

#include "FVEnemyAIController.h"
#include "Components/CapsuleComponent.h"

void AFVBossEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (m_bIsSpinning)
	{
		const float rotationThisFrame = m_SpinSpeed * DeltaSeconds;

		AddActorLocalRotation(FRotator(0, rotationThisFrame, 0));
		m_AccumulatedRotation += rotationThisFrame;
		if (m_AccumulatedRotation >= 360.0f)
		{
			m_bIsSpinning = false;
		}
	}
}

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

	if (IsDead)
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

void AFVBossEnemy::Spin(float duration)
{
	if (duration <= 0)
	{
		return;
	}

	m_SpinSpeed = 360.0f / duration;
	m_AccumulatedRotation = 0.0f;
	m_bIsSpinning = true;
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