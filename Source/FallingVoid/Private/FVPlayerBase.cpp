// Copyright: Falling Void Studios


#include "FVPlayerBase.h"

// Sets default values
AFVPlayerBase::AFVPlayerBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFVPlayerBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFVPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFVPlayerBase::Attack()
{

}


// Called to bind functionality to input
void AFVPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}