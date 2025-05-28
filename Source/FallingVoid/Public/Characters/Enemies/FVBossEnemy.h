// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "FVBossEnemy.generated.h"

UENUM(Blueprintable)
enum class EBossState : uint8
{
	None = 0	UMETA(DisplayName = "None"),
	/* Attacking the player */
	Attacking	UMETA(DisplayName = "Attacking"),
	/* After his health gets below 50% the boss will retreat */
	Retreating  UMETA(DisplayName = "Retreating"),
	/* The boss is dead */
	Dead		UMETA(DisplayName = "Dead"),
	/* The boss is moving around */
	Moving		UMETA(DisplayName = "Moving"),
	/* The boss is Jumping out or into the arena */
	Jumping		UMETA(DisplayName = "Jumping"),
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss State")
	EBossState BossState = { EBossState::None };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Boss")
	bool IsDead = { false };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy|Boss")
	class UCapsuleComponent* CollisionComponent;

	UFUNCTION(BlueprintCallable)
	void ResetCollision();

	UFUNCTION(BlueprintImplementableEvent, Category = "Stun")
	void OnAttackBegin();

	virtual void Attack() override;

	virtual void TakeDamage(float damage) override;

private:

	FTimerHandle m_TimerHandler;
};
