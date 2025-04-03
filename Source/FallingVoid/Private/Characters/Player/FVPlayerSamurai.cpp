// Copyright: Falling Void Studios


#include "Characters/Player/FVPlayerSamurai.h"

#include "FVGlobals.h"
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
    //UE_LOG(LogTemp, Warning, TEXT("Started Attacking %s"), *GetNameSafe(result.GetActor()));
    AFVEnemyBase* enemy = Cast<AFVEnemyBase>(result.GetActor());
    if (enemy)
    {
        float damageMultiplier = 1.f;
        if (result.Distance > MaxAttackRange)
        {
            damageMultiplier = FMath::Lerp(
                1.f,
                MinDamageMultiplier,
                FMath::Clamp((result.Distance - MaxAttackRange) / (MinDamageRange - MaxAttackRange), 0.f, 1.f)
            );
        }

        const float finalDamage = BaseDamage * DamageBoost * damageMultiplier;

        enemy->TakeDamage(finalDamage);
    	UE_LOG(LogTemp, Warning, TEXT("Attacked Enemy at distance: %.2f, Damage multiplier: %.2f, Final damage: %.2f"),
        result.Distance, damageMultiplier, finalDamage);
    }
}

void AFVPlayerSamurai::SetCollisionEnabled(bool enabled)
{
    CollisionComponent->SetCollisionEnabled(enabled ? ECollisionEnabled::Type::QueryOnly : ECollisionEnabled::Type::NoCollision);
}

FHitResult AFVPlayerSamurai::FireRaycast()
{
    FVector startLocation = CollisionComponent->GetComponentLocation();
    FRotator rotation = GetActorRotation();
    FVector endTrace = startLocation + (rotation.Vector() * AttackRange);;

    FCollisionQueryParams traceParams(SCENE_QUERY_STAT(Shoot), true, GetInstigator());
    FHitResult hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(hit, startLocation, endTrace, ECC_Visibility, traceParams);

    /*DrawDebugLine(
        GetWorld(),
        startLocation,
        endTrace,
        bHit ? FColor::Red : FColor::Green,
        false, // Persistent lines
        5.0f,  // Duration (seconds)
        0,     // Depth priority
        2.0f   // Thickness
    );*/

    return hit;
}
