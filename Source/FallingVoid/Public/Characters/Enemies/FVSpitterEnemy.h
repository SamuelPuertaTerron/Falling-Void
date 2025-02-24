// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "FVSpitterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVSpitterEnemy : public AFVEnemyBase
{
	GENERATED_BODY()

public:
	virtual void Attack() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AActor> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FVector ShootingPosition{};

protected:

};
