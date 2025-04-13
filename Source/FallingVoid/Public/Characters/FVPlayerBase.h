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
	Pinned	 UMETA(DisplayName = "Pinned"),
};

UENUM(Blueprintable)
enum class EPlayerInteractionState : uint8
{
	None = 0	 UMETA(DisplayName = "None"),
	Reviving	 UMETA(DisplayName = "Reviving"),
	MedkitReviving	 UMETA(DisplayName = "Medkit Reviving"),
	Healing		 UMETA(DisplayName = "Healing"),
	OtherHealing UMETA(DisplayName = "Healing Other"),
	BeingHealing UMETA(DisplayName = "Being Healing"),
	Trapping	 UMETA(DisplayName = "Trapping"),
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", DisplayName = "Player Interaction State")
	EPlayerInteractionState PlayerInteractionState{ EPlayerInteractionState::None };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float MouseSensitivity{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player")
	int MedkitsAmount{ 0 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int TrapAmount{ 0 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int SkillPoints{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float Armour{ 0 };

	bool GetIsDeadOrDowned() const;
	bool GetIsAlive() const;

	UFUNCTION(BlueprintCallable, DisplayName = "Set Player Interaction State")
	void SetInteractionState(const EPlayerInteractionState& state);

	UFUNCTION(BlueprintPure, DisplayName = "GetPlayerInteractionState")
	EPlayerInteractionState GetInteractionState() const;

	UFUNCTION(BlueprintPure, DisplayName = "GetIsDeadOrDowned")
	bool NodeGetIsDeadOrDowned() const;
	UFUNCTION(BlueprintPure, DisplayName = "GetIsAlive")
	bool NodeGetIsAlive() const;
	// Event that gets called when the Character had died. Implemneted all base characters.
	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void OnTakenDamageLate();

	virtual void TakeDamage(float damage) override;

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

private:
	EPlayerInteractionState m_CurrentInteractionState;
};
