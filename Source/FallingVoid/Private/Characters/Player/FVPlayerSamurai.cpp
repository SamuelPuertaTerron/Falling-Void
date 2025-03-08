// Copyright: Falling Void Studios


#include "Characters/Player/FVPlayerSamurai.h"
#include "Components/CapsuleComponent.h"

void AFVPlayerSamurai::Attack()
{
    if (!CollisionComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("Collision Component has not been set in the inspector"));
        return;
    }

    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    GetWorld()->GetTimerManager().SetTimer(m_TimerHandler, this, &AFVPlayerSamurai::ResetCollision, 0.5f, false);
}

void AFVPlayerSamurai::SetCollision(UCapsuleComponent* component)
{
	CollisionComponent = component;
}

void AFVPlayerSamurai::ResetCollision()
{

}
