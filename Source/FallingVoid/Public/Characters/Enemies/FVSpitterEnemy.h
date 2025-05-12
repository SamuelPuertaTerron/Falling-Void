// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "FVSpitterEnemy.generated.h"

class AFVProjectile;
/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVSpitterEnemy : public AFVEnemyBase
{
	GENERATED_BODY()

public:
	AFVSpitterEnemy();

	virtual void Attack() override;

	virtual void TakeDamage(float damage) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AFVProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FVector ShootingPosition{};

protected:

};
