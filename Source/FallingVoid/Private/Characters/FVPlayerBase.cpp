// Copyright: Falling Void Studios


#include "Characters/FVPlayerBase.h"


// Sets default values
AFVPlayerBase::AFVPlayerBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFVPlayerBase::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("AFVPlayerBase::Attack() called"));

	//Super::Attack();
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

// Called to bind functionality to input
void AFVPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}