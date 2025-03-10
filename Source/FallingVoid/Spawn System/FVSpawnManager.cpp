// Copyright: Falling Void Studios


#include "FVSpawnManager.h"
#include "Characters/Enemies/FVEnemyBase.h"
#include "FVEnemyAIController.h"

// Sets default values
AFVSpawnManager::AFVSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFVSpawnManager::SpawnEnemies()
{
	for (int i = 0; i < MaxSpawnAmount; i++)
	{
		FVector spawnLocation = SpawnPositionList[FMath::RandRange(0, SpawnPositionList.Max() - 1)].Get()->GetActorLocation();
		FRotator spawnRotation = SpawnPositionList[FMath::RandRange(0, SpawnPositionList.Max() - 1)].Get()->GetActorRotation();

		TSubclassOf<AFVEnemyBase> spawnEnemy = EnemiesList[FMath::RandRange(0, EnemiesList.Max() - 1)];

		AFVEnemyBase* enemy = GetWorld()->SpawnActor<AFVEnemyBase>(spawnEnemy, spawnLocation, spawnRotation);
		/*AFVEnemyAIController* enemyController = Cast<AFVEnemyAIController>(enemy->GetController());

		enemyController->SetupPerception();*/
	}
}

// Called when the game starts or when spawned
void AFVSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFVSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

