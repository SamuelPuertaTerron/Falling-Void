// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "../Spawn System/FVSpawnManager.h"

#include "FVSpawnManagerSubsystem.generated.h"

/**
 * Utility class to grab spawn manager quickly (Already done in Blueprints, but need a way to do this in C++)
 */
UCLASS()
class FALLINGVOID_API UFVSpawnManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/* Sets the spawn manager inside BP as we cache it inside the Game Instance BP */
	UFUNCTION(BlueprintCallable, Category="SpawnManagerSubsystem")
	void SetSpawnManager(AFVSpawnManager* manager);

	AFVSpawnManager* GetSpawnManager() const;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
private :
	UPROPERTY()
	AFVSpawnManager* m_SpawnManager;
};
