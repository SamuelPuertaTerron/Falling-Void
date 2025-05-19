// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "FVBossEnemy.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVBossEnemy : public AFVEnemyBase
{
	GENERATED_BODY()

public:
	virtual void Stun(float delay) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Boss", meta = (AllowPrivateAccess = "true"))
	float AttackRangeForDistance = { 1000.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Boss")
	float  AttackChance = { 0.3f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Boss")
	float  SprintSpeed = { 1200.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Boss")
	float  WalkSpeed = { 600.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Boss")
	float TimeBetweenAttacks = { 0.25f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Boss")
	bool IsComboAAttacking = { false };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Boss")
	bool IsComboBAttacking = { false };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Boss")
	bool IsComboCAttacking = { false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Boss|Anims")
	UAnimMontage*  ShortAttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Boss|Anims")
	UAnimMontage* SprintMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy|Boss")
	class UCapsuleComponent* CollisionComponent;

	virtual void Attack() override;

	virtual void TakeDamage(float damage) override;

private:
	void ResetCollision();

	FTimerHandle m_TimerHandler;
};
