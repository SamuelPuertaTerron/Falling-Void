// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FVSpawnPoint.generated.h"

/*
 * This represents a spawn point within the game world. 
 */
UCLASS()
class FALLINGVOID_API AFVSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFVSpawnPoint();

	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	bool IsDebug{ true };
};
