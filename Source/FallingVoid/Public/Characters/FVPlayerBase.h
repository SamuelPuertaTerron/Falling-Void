// Copyright: Falling Void Studios
// This is the Base Player character class, this will contain the base scripts for the 

#pragma once

#include "CoreMinimal.h"
#include "Characters/FVBaseCharacter.h"
#include "FVPlayerBase.generated.h"

UCLASS()
class FALLINGVOID_API AFVPlayerBase : public AFVBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFVPlayerBase();

	// Down timer will be the timer that the player is down on the ground before dying
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float DownTimer{ 0.5f };


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float MouseSensitivity{ 1.0f };

	virtual void Attack() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
