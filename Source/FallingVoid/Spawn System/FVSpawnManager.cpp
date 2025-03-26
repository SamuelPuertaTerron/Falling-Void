// Copyright: Falling Void Studios


#include "FVSpawnManager.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "FVEnemyAIController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFVSpawnManager::AFVSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CurrentWaveIndex = -1;
}

void AFVSpawnManager::StartWave()
{
	EnemiesRemaining = 0;

	SpawnEnemies();
}

void AFVSpawnManager::StartNextWave()
{
    CurrentWaveIndex++;
    UE_LOG(LogTemp, Warning, TEXT("Started Wave! %d"), CurrentWaveIndex);

    if (Waves.IsValidIndex(CurrentWaveIndex))
    {
        StartWaveAfterDelay(Waves[CurrentWaveIndex].WaveDelay);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("All Waves Completed!"));
        OnAllWavesCompleted();
    }
}

// Called when the game starts or when spawned
void AFVSpawnManager::BeginPlay()
{
    Super::BeginPlay();

    // Find all SpawnPoint actors in the level
    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFVSpawnPoint::StaticClass(), foundActors);

    // Cast AActor* to AFVSpawnPoint* and store them in SpawnPoints
    for (AActor* actor : foundActors)
    {
        if (AFVSpawnPoint* spawnPoint = Cast<AFVSpawnPoint>(actor))
        {
            SpawnPoints.Add(spawnPoint);
        }
    }
}

void AFVSpawnManager::SpawnEnemies()
{
    UWorld* world = GetWorld();
    if (!world) return;

    if (!Waves.IsValidIndex(CurrentWaveIndex))
        return;

    FSpawnWaveData currentWave = Waves[CurrentWaveIndex];

    for (const FEnemySpawnData& enemyData : currentWave.EnemySpawnDatas)
    {
        for (int32 i = 0; i < enemyData.Count; i++)
        {
            int randomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);

            if (!SpawnPoints.IsValidIndex(randomIndex))
            {
                UE_LOG(LogTemp, Warning, TEXT("Spawn Point index out of range. Size of SpawnPoints is %d"), SpawnPoints.Num());
                continue;
            }

            const AFVSpawnPoint* point = SpawnPoints[randomIndex];

            FVector spawnLocation = point->GetActorLocation() + (FMath::VRand() * SpawnRadius);

            FActorSpawnParameters spawnParams;
            spawnParams.Owner = this;
            spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            AFVEnemyBase* spawnedEnemy = world->SpawnActor<AFVEnemyBase>(enemyData.EnemyClass, spawnLocation, FRotator::ZeroRotator, SpawnParams);
            if (spawnedEnemy)
            {
                ActiveEnemies.Add(spawnedEnemy);
                EnemiesRemaining++;
    
                // Bind to the enemy's OnDestroyed event
                spawnedEnemy->OnDestroyed.AddDynamic(this, &AFVSpawnManager::OnEnemyDestroyed);
            }
        }
    }
}

void AFVSpawnManager::OnEnemyDestroyed(AActor* enemy)
{
    ActiveEnemies.Remove(enemy);
    EnemiesRemaining--;

    if (EnemiesRemaining <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Wave Completed"));
        OnWaveCompleted();
        StartNextWave();
    }
}

void AFVSpawnManager::StartWaveAfterDelay(float Delay)
{
    GetWorld()->GetTimerManager().SetTimer(m_WaveTimerHandle, this, &AFVSpawnManager::StartWave, Delay, false);
}

// Called every frame
void AFVSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

