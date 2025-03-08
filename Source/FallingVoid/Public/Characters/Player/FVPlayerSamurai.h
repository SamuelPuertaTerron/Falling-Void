// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/FVPlayerBase.h"
#include "FVPlayerSamurai.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVPlayerSamurai : public AFVPlayerBase
{
	GENERATED_BODY()

	AFVPlayerSamurai() = default;

public:
	virtual void Attack() override;

	UFUNCTION(BlueprintCallable, Category = "Player|Samurai")
	void SetCollision(class UCapsuleComponent* component);

	//Uproperty defines here
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Samurai")
	class UCapsuleComponent* CollisionComponent = nullptr;

private:
	void ResetCollision();

private:
	FTimerHandle m_TimerHandler;
};
