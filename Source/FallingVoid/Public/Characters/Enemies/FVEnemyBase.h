// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/FVBaseCharacter.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "FVEnemyBase.generated.h"

class AFVEnemyAIController;
/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVEnemyBase : public AFVBaseCharacter
{
	GENERATED_BODY()
public:
		UBehaviorTree* GetBehaviorTree() const
		{
			return BehaviorTree;
		}

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		float FireRate = { 0.5f };

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		float AttackRange = { 1000.0f };

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		float AttackTime = { 0.5f };


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		float SpeedModifer = { 600.0f };

		/** This walk speed is cache in begin play */
		UPROPERTY(VisibleAnywhere)
		float CacheWalkSpeed;


		/** Returns the damage from this enemy which is the base damage x damage boost. */
		UFUNCTION(BlueprintPure, Category = "Enemy")
		float GetDamage() const;

		/** Sets the movement speed of this enemy */
		UFUNCTION(BlueprintCallable, Category = "Enemy")
		void SetWalkSpeed(float modifier = -1);

		/** Gets called whenever the enemy takes damage. Calls the OnTakeDamage() blueprint event. */
		virtual void TakeDamage(float damage) override;

		/** Make the enemy not able to move or attack for a delay */
		UFUNCTION(BlueprintCallable, Category="Enemy")
		void Stun(float delay);

		/** Stops movement of the current enemy */
		void StopMovement() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float FireRange{ 1000.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UBehaviorTree* BehaviorTree{};

	void SetCapsuleCollision() const;

protected:

	virtual void BeginPlay() override;

	FHitResult Shoot();

private:
	FTimerHandle m_SunTimer;

	UPROPERTY()
	AFVEnemyAIController* m_pController;
};
