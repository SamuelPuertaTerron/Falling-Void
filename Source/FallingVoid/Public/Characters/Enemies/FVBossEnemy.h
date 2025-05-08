// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "FVBossEnemy.generated.h"

/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVBossEnemy : public AFVEnemyBase
{
	GENERATED_BODY()

public:
	virtual void Stun(float delay) override;
};
