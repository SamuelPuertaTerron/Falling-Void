// Copyright: Falling Void Studios


#include "FVSpawnPoint.h"

// Sets default values
AFVSpawnPoint::AFVSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFVSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFVSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

