// Copyright: Falling Void Studios


#include "SpawnSystem/FVSpawnManager.h"

#include "Characters/Enemies/FVEnemyBase.h"
#include "FVGlobals.h"
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
    CurrentWave = CurrentWaveIndex; //Note: Current wave is a different variable as I don't really want the CurrentWaveIndex modifable in BP.

    OnWaveChanged(CurrentWave);

    if (Waves.IsValidIndex(CurrentWaveIndex))
    {
        StartWaveAfterDelay(Waves[CurrentWaveIndex].WaveDelay);
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("All Waves Completed!"));
        OnAllWavesCompleted();
    }
}

void AFVSpawnManager::StartNextWaveAfterDelay(float delay, int currentWaveIndex)
{
    CurrentWaveIndex = currentWaveIndex;
    StartWaveAfterDelay(delay);
}

int AFVSpawnManager::GetMaxEnemiesThisWave()
{
    int enemyCount{ 0 };

    if (!Waves.IsValidIndex(CurrentWaveIndex))
        return -1;

    FSpawnWaveData currentWave = Waves[CurrentWaveIndex];

    for (const FEnemySpawnData& enemyData : currentWave.EnemySpawnDatas)
    {
        enemyCount += enemyData.Count;
    }

    return enemyCount;
}

float AFVSpawnManager::GetSpawnRadius() const
{
    return SpawnRadius;
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

    MaxWaves = Waves.Num();
    //UE_LOG(LogTemp, Warning, TEXT("Max Waves: %d"), MaxWaves);
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
                continue;
            }

            const AFVSpawnPoint* point = SpawnPoints[randomIndex];

            // Calculate potential spawn location
            FVector spawnLocation = point->GetActorLocation() + (FMath::VRand() * SpawnRadius);
            spawnLocation.Z += SpawnHeightOffset;
            FRotator spawnRotation = FRotator::ZeroRotator;

            FActorSpawnParameters spawnParams;
            spawnParams.Owner = this;
            spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

            AFVEnemyBase* spawnedEnemy = world->SpawnActor<AFVEnemyBase>(enemyData.EnemyClass, spawnLocation, spawnRotation, spawnParams);
            if (spawnedEnemy)
            {
                spawnedEnemy->OnDestroyed.AddDynamic(this, &AFVSpawnManager::OnEnemyDestroyed);

                ActiveEnemies.Add(spawnedEnemy);
                EnemiesRemaining++;
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

