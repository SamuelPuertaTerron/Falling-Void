// Copyright: Falling Void Studios


#include "Characters/Enemies/FVSpitterEnemy.h"

void AFVSpitterEnemy::Attack()
{
	if (!Projectile) return;

    UWorld* World = GetWorld();
    if (!World) return; // Ensure world is valid

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //Ignores Collision

    FVector SpawnLocation = ShootingPosition;
    FRotator SpawnRotation = GetActorRotation(); // Face same direction as enemy

    // Spawn the projectile
    AActor* SpawnedProjectile = World->SpawnActor<AActor>(Projectile, SpawnLocation, SpawnRotation, SpawnParams);

    if (SpawnedProjectile)
    {
        UE_LOG(LogTemp, Warning, TEXT("Projectile spawned successfully!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn projectile!"));
    }
}
