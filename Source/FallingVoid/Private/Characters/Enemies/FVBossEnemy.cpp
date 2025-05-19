// Copyright: Falling Void Studios


#include "Characters/Enemies/FVBossEnemy.h"

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

    GetWorld()->GetTimerManager().SetTimer(m_TimerHandler, this, &AFVBossEnemy::ResetCollision, TimeBetweenAttacks, false);
}

void AFVBossEnemy::TakeDamage(float damage)
{
	Super::TakeDamage(damage);
}

void AFVBossEnemy::ResetCollision()
{
    IsComboAAttacking = false;
    IsComboBAttacking = false;
    IsComboCAttacking = false;

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorldTimerManager().ClearTimer(m_TimerHandler);
}