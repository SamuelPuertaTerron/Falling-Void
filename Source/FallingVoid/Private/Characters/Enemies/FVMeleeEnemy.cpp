// Copyright: Falling Void Studios


#include "Characters/Enemies/FVMeleeEnemy.h"
#include "Components/CapsuleComponent.h"

AFVMeleeEnemy::AFVMeleeEnemy()
{
    //CollisionComponent = nullptr;
}

void AFVMeleeEnemy::Attack()
{
    if (!CollisionComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("Collision Component has not been set in the inspector"));
        return;
    }

    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    GetWorld()->GetTimerManager().SetTimer(m_TimerHandler, this, &AFVMeleeEnemy::ResetCollision, 0.5f, false);
}

void AFVMeleeEnemy::SetCollision(UCapsuleComponent* component)
{
    CollisionComponent = component;
}

void AFVMeleeEnemy::ResetCollision()
{
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    GetWorldTimerManager().ClearTimer(m_TimerHandler);
}
 