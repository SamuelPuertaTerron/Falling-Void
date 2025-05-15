// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "FVHunterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVHunterEnemy : public AFVEnemyBase
{
	GENERATED_BODY()

public:
	virtual void Attack() override;
	virtual void TakeDamage(float damage) override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerAlive();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	bool IsPlayerPinned { false };

private:
	FTimerHandle m_TimeHandle;
};
