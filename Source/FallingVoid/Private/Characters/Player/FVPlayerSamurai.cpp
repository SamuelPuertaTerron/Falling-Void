// Copyright: Falling Void Studios


#include "Characters/Player/FVPlayerSamurai.h"

#include "Characters/Enemies/FVEnemyBase.h"
#include "Components/CapsuleComponent.h"

void AFVPlayerSamurai::Attack()
{
    if (!CollisionComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("Collision Component has not been set in the inspector"));
        return;
    }

    // Enable collision at start of attack
    SetCollisionEnabled(true);

    // Set timer to disable collision after attack duration
    GetWorld()->GetTimerManager().SetTimer(m_TimerHandler, [this]()
        {
            SetCollisionEnabled(false);
        }, AttackDuration, false);
}

void AFVPlayerSamurai::SetCollision(UCapsuleComponent* component)
{
	CollisionComponent = component;

    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFVPlayerSamurai::OnWeaponBeginOverlap);

    SetCollisionEnabled(false);
}


void AFVPlayerSamurai::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this)
        return;

    AFVEnemyBase* enemy = Cast<AFVEnemyBase>(OtherActor);
    if (enemy)
    {
        const float DistanceToEnemy = FVector::Distance(GetActorLocation(), enemy->GetActorLocation());

        float DamageMultiplier = 1.f;
        if (DistanceToEnemy > MaxAttackRange)
        {
            DamageMultiplier = FMath::Lerp(
                1.f,
                MinDamageMultiplier,
                FMath::Clamp((DistanceToEnemy - MaxAttackRange) / (MinDamageRange - MaxAttackRange), 0.f, 1.f)
            );
        }

        const float FinalDamage = BaseDamage * DamageBoost * DamageMultiplier;

        enemy->TakeDamage(FinalDamage);
        enemy->OnTakenDamage();
        UE_LOG(LogTemp, Warning, TEXT("Attacked Enemy at distance: %.2f, Damage multiplier: %.2f, Final damage: %.2f"),
            DistanceToEnemy, DamageMultiplier, FinalDamage);
    	// Optional: Spawn hit effect at SweepResult.Location
    }
}

void AFVPlayerSamurai::SetCollisionEnabled(bool enabled)
{
    CollisionComponent->SetCollisionEnabled(enabled ? ECollisionEnabled::Type::QueryOnly : ECollisionEnabled::Type::NoCollision);
}
