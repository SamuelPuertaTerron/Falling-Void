// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "FVMeleeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVMeleeEnemy : public AFVEnemyBase
{
	GENERATED_BODY()

public:
	AFVMeleeEnemy();

	virtual void Attack() override;

	//Uproperty defines here
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy")
	class UCapsuleComponent* CollisionComponent;

private:
	void ResetCollision();

private:
	FTimerHandle m_TimerHandler;
};
