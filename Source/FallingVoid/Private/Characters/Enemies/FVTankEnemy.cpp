// Copyright: Falling Void Studios


#include "Characters/Enemies/FVTankEnemy.h"
#include "Components/CapsuleComponent.h"

AFVTankEnemy::AFVTankEnemy()
{
    // Initialize the CollisionComponent
    auto mesh = TSubclassOf<USkeletalMeshComponent>();

    CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Attack Collision"));
    CollisionComponent->SetupAttachment(GetMesh(), "hand_r");

    SetCapsuleCollision();
}

void AFVTankEnemy::Attack()
{
    if (CollisionComponent == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Collision Component has not been set in the inspector"));
        return;
    }

    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    GetWorld()->GetTimerManager().SetTimer(m_TimerHandler, this, &AFVTankEnemy::ResetCollision, FireRate, false);
}

void AFVTankEnemy::ResetCollision()
{
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    GetWorldTimerManager().ClearTimer(m_TimerHandler);
}
