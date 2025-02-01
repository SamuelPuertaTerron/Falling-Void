// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/FVBaseCharacter.h"
#include "FVEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVEnemyBase : public AFVBaseCharacter
{
	GENERATED_BODY()
public:
		virtual void Attack() override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float FireRange{ 1000.0f };

private:

	FHitResult Shoot();
};
