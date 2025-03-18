// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FVSpawnPoint.h"

#include "FVSpawnManager.generated.h"

class AFVEnemyBase;

USTRUCT(BlueprintType)
struct FEnemySpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> EnemyClass; // The enemy type to spawn

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count; // Number of this enemy type to spawn
};

USTRUCT(BlueprintType)
struct FSpawnWaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEnemySpawnData> EnemySpawnDatas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaveDelay;
};

UCLASS()
class FALLINGVOID_API AFVSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFVSpawnManager();

	UFUNCTION(BlueprintCallable)
	void StartWave();

	UFUNCTION(BlueprintCallable)
	void StartNextWave();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnEnemies();

	UFUNCTION()
	void OnEnemyDestroyed(AActor* enemy);

	UFUNCTION(BlueprintImplementableEvent, Category = "Spawning")
	void OnWaveCompleted();
	UFUNCTION(BlueprintImplementableEvent, Category = "Spawning")
	void OnAllWavesCompleted();
private:
	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	TArray<AFVSpawnPoint*> SpawnPoints;

	// Array of active enemies
	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	TArray<AActor*> ActiveEnemies;

	// Track the number of enemies left
	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	int32 EnemiesRemaining;

	// Array of waves
	UPROPERTY(EditAnywhere, Category = "Waves")
	TArray<FSpawnWaveData> Waves;

	// Current wave index
	UPROPERTY(VisibleAnywhere, Category = "Waves")
	int32 CurrentWaveIndex;

	// Timer handle for wave spawning
	FTimerHandle m_WaveTimerHandle;

	void StartWaveAfterDelay(float Delay);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
