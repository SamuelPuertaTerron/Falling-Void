// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/FVBaseCharacter.h"
#include "FVPlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVPlayerBase : public AFVBaseCharacter
{
	GENERATED_BODY()

public:
	
	AFVPlayerBase();

	// Health and MaxHealth should be editable and visible in Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float DownTimer { 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float CameraSensitivity{ 0.5f };

	// Attack function that is callable in Blueprints
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
