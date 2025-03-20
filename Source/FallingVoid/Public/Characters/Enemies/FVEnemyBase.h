// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/FVBaseCharacter.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "FVEnemyBase.generated.h"

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

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float SightRadius = { 1500.0f };

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float LoseSightRadius = { 25.0f };

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float VisionConeAngle = { 90.0f };

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float MaxAge = { 5.0f };

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		float FireRate = { 0.5f };

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		float AttackRange = { 1000.0f };

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		float AttackTime = { 0.5f };

		UFUNCTION(BlueprintPure, Category = "Enemy")
		float GetDamage();

		//An Event which gets called from BP when a bullet is shot
		UFUNCTION(BlueprintImplementableEvent)
		void OnTakenDamage();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float FireRange{ 1000.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UBehaviorTree* BehaviorTree{};

protected:

	FHitResult Shoot();
};
