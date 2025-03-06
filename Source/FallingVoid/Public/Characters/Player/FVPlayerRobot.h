// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/FVPlayerBase.h"
#include "FVPlayerRobot.generated.h"

class AFVEnemyBase;

USTRUCT(Blueprintable)
struct FHitItem
{
	GENERATED_BODY()

	//Only set if it has hit the enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AFVEnemyBase* Enemy;
	//Set if it has hit anything but the enemy (Use the Enemy variable instead)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Actor;
	//The location of the hit 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
	//The rotation of the hit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Rotation;
};

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
	int MaxAmmo{ 100 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Robot")
	int CurrentAmmo{ 100 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player|Robot")
	bool IsReloading{ false };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Robot")
	bool IsShielding{ false };

	//An Event which gets called from BP when a bullet is shot
	UFUNCTION(BlueprintImplementableEvent)
	void OnBulletShot(FHitItem item);

public:

	UFUNCTION(BlueprintCallable)
	void StartReload();
	UFUNCTION(BlueprintCallable)
	void EndReload();


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
