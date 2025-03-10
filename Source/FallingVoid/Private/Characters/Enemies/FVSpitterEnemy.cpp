// Copyright: Falling Void Studios


#include "Characters/Enemies/FVSpitterEnemy.h"
#include "FVProjectile.h"

void AFVSpitterEnemy::Attack()
{
	if (!Projectile) return;

    UWorld* World = GetWorld();
    if (!World) return; // Ensure world is valid

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //Ignores Collision

    FRotator SpawnRotation = GetActorRotation();

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
