// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/FVPlayerBase.h"
#include "FVPlayerRobot.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVPlayerRobot : public AFVPlayerBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Robot")
	float FireRate{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Robot")
	float FireRange{ 1000.0f };
public:

	virtual void Attack() override;

private:
	FHitResult Shoot();
};
