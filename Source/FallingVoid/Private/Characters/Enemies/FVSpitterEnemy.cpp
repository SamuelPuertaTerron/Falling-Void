// Copyright: Falling Void Studios


#include "Characters/Enemies/FVSpitterEnemy.h"
#include "FVProjectile.h"

AFVSpitterEnemy::AFVSpitterEnemy()
{
    SetCapsuleCollision();
}

void AFVSpitterEnemy::Attack()
{
    if (!Projectile) return;

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    FRotator SpawnRotation = GetActorRotation();


    OnAttackPlayer();

    // Spawn the projectile
    AFVProjectile* spawnedProjectile = World->SpawnActor<AFVProjectile>(Projectile, ShootingPosition, SpawnRotation, SpawnParams);

   if (spawnedProjectile)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Projectile spawned successfully!"));
        float damage = BaseDamage * DamageBoost;
        spawnedProjectile->SetDamage(damage);
    }
    else
    {
        //UE_LOG(LogTemp, Error, TEXT("Failed to spawn projectile!"));
    }
}

void AFVSpitterEnemy::TakeDamage(float damage)
{
    Super::TakeDamage(damage);
}
