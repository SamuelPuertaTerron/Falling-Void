// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FVBaseCharacter.h"

#include "FVGlobals.h"

// Sets default values
AFVBaseCharacter::AFVBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFVBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFVBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFVBaseCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Base Character Attack called"));
}

void AFVBaseCharacter::TakeDamage(float damage)
{
	//UE_LOG(LogTemp, Error, TEXT("Override Me!"));
}

// Called to bind functionality to input
void AFVBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

