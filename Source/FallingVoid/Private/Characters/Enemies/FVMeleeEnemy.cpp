// Copyright: Falling Void Studios


#include "Characters/Enemies/FVMeleeEnemy.h"
#include "Components/CapsuleComponent.h"

AFVMeleeEnemy::AFVMeleeEnemy()
{
    // Initialize the CollisionComponent
    auto mesh = TSubclassOf<USkeletalMeshComponent>();

    CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Attack Collision"));
    CollisionComponent->SetupAttachment(GetMesh(), "hand_r");
}

void AFVMeleeEnemy::Attack()
{
    if (CollisionComponent == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Collision Component has not been set in the inspector"));
        return;
    }

    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    GetWorld()->GetTimerManager().SetTimer(m_TimerHandler, this, &AFVMeleeEnemy::ResetCollision, FireRate, false);
}

void AFVMeleeEnemy::ResetCollision()
{
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    GetWorldTimerManager().ClearTimer(m_TimerHandler);
}
 