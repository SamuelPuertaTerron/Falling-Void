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

    FHitResult result = FireRaycast();

    AFVEnemyBase* enemy = Cast<AFVEnemyBase>(result.GetActor());
    if (enemy)
    {
        const float distanceToEnemy = FVector::Distance(GetActorLocation(), enemy->GetActorLocation());

        float damageMultiplier = 1.f;
        if (distanceToEnemy > MaxAttackRange)
        {
            damageMultiplier = FMath::Lerp(
                1.f,
                MinDamageMultiplier,
                FMath::Clamp((distanceToEnemy - MaxAttackRange) / (MinDamageRange - MaxAttackRange), 0.f, 1.f)
            );
        }

        const float finalDamage = BaseDamage * DamageBoost * damageMultiplier;

        enemy->TakeDamage(finalDamage);
        enemy->OnTakenDamage();
        UE_LOG(LogTemp, Warning, TEXT("Attacked Enemy at distance: %.2f, Damage multiplier: %.2f, Final damage: %.2f"),
            distanceToEnemy, damageMultiplier, finalDamage);
    	// Optional: Spawn hit effect at SweepResult.Location
    }
}

void AFVPlayerSamurai::SetCollisionEnabled(bool enabled)
{
    CollisionComponent->SetCollisionEnabled(enabled ? ECollisionEnabled::Type::QueryOnly : ECollisionEnabled::Type::NoCollision);
}

FHitResult AFVPlayerSamurai::FireRaycast()
{
    FVector location = GetActorLocation();
    FRotator rotation = GetActorRotation();
    FVector endTrace = FVector::ZeroVector;

    const APlayerController* playerController = GetWorld()->GetFirstPlayerController();

    if (playerController)
    {
        playerController->GetPlayerViewPoint(location, rotation);
        endTrace = location + (rotation.Vector() * MaxAttackRange);
    }

    FCollisionQueryParams traceParams(SCENE_QUERY_STAT(Shoot), true, GetInstigator());
    FHitResult hit(ForceInit);
    GetWorld()->LineTraceSingleByChannel(hit, location, endTrace, ECC_Visibility, traceParams);

    return hit;
}
