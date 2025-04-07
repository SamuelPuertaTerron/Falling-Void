// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "FVTankEnemy.generated.h"

/**
 * Acts the same as the melee enemy, just made this class to add additionally content if we wanted to. 
 */
UCLASS()
class FALLINGVOID_API AFVTankEnemy : public AFVEnemyBase
{
	GENERATED_BODY()

public:
	AFVTankEnemy();
	~AFVTankEnemy() = default;

	virtual void Attack() override;

	//Uproperty defines here
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy")
	class UCapsuleComponent* CollisionComponent;

private:
	/** Reset the attacking collision to no collision when none attacking */
	void ResetCollision();

private:
	FTimerHandle m_TimerHandler;
};
