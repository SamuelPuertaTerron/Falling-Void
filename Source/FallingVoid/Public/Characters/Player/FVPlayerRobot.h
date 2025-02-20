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
	float FireRate{ 600.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Robot")
	float FireRange{ 1000.0f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Robot")
	int MaxAmmo{ 10 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Robot")
	int CurrentAmmo{ 10 };


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Robot")
	bool IsShielding{ false };
public:



	UFUNCTION(BlueprintCallable)
	void StartShooting();
	UFUNCTION(BlueprintCallable)
	void EndShooting();

	virtual void Attack() override;
private:
	float m_TimeBetweenShots;
	FTimerHandle m_TimeBetweenShotsTimeHandle;
private:
	FHitResult Shoot();
};
