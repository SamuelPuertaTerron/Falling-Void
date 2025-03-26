// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/FVPlayerBase.h"
#include "FVPlayerSamurai.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVPlayerSamurai : public AFVPlayerBase
{
	GENERATED_BODY()

	AFVPlayerSamurai() = default;

public:
	virtual void Attack() override;

	UFUNCTION(BlueprintCallable, Category = "Player|Samurai")
	void SetCollision(class UCapsuleComponent* component);

	UFUNCTION()
	void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);


	//Uproperty defines here
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Samurai")
	class UCapsuleComponent* CollisionComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Samurai")
	float AttackDuration{ 0.25f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Samurai")
	float MaxAttackRange{ 500.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Samurai")
	float MinDamageRange{ 100.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Samurai")
	float MinDamageMultiplier{ 0.3f };

private:
	void SetCollisionEnabled(bool enabled);

private:
	FTimerHandle m_TimerHandler;
};
