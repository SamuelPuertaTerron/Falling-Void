// Copyright: Falling Void Studios
// This is the base Character class for both the Player Character and the AI characters

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FVBaseCharacter.generated.h"

UCLASS()
class FALLINGVOID_API AFVBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFVBaseCharacter();

	// Health and MaxHealth should be editable and visible in Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float Health{ 100 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float MaxHealth{ 100 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float BaseDamage{ 10.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float DamageBoost { 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float DamageReduction{ 1.0f };

	// Attack function that gets called. 
	UFUNCTION(BlueprintCallable, Category = "Player")
	virtual void Attack();

	// Function to take damage
	UFUNCTION(BlueprintCallable, Category = "Player")
	void TakeDamage(float damage);

	// Event that gets called when the Character had died. Implemneted all base characters.
	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
	void OnDied();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
