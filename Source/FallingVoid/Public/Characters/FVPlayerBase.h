// Copyright: Falling Void Studios
// This is the Base Player character class, this will contain the base scripts for the 

#pragma once

#include "CoreMinimal.h"
#include "Characters/FVBaseCharacter.h"
#include "FVPlayerBase.generated.h"

UENUM(Blueprintable)
enum class EPlayerHealthState : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Alive	 UMETA(DisplayName = "Alive"),
	Downed   UMETA(DisplayName = "Downed"),
	Dead     UMETA(DisplayName = "Dead"),
};

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
	//The current player state for the health system. All Done in Blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", DisplayName = "Player State")
	EPlayerHealthState PlayerHealthState{ EPlayerHealthState::Alive };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float MouseSensitivity{ 1.0f };

	virtual void Attack() override;


	bool GetIsDeadOrDowned() const;
	bool GetIsAlive() const;

	UFUNCTION(BlueprintPure, DisplayName = "GetIsDeadOrDowned")
	bool NodeGetIsDeadOrDowned() const;
	UFUNCTION(BlueprintPure, DisplayName = "GetIsAlive")
	bool NodeGetIsAlive() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	class UAIPerceptionStimuliSourceComponent* StimuliSource;

	void SetupStimuliSource();
};
