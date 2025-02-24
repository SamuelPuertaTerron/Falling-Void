// Copyright: Falling Void Studios


#include "FVProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Characters/FVPlayerBase.h"
#include "Characters/Player/FVPlayerRobot.h"


// Sets default values
AFVProjectile::AFVProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitialLifeSpan = LifeSpan;
}

void AFVProjectile::SetDamage(float damage)
{
	Damage = damage;
}

// Called when the game starts or when spawned
void AFVProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFVProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

