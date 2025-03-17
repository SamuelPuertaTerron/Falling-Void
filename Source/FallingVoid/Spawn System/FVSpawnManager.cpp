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

void AFVSpawnManager::SpawnEnemies(const FSpawnCollection& collection)
{
	// Check if there are any spawn positions or enemy types defined
	if (collection.SpawnPositionList.Num() == 0 || collection.EnemiesList.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No spawn positions or enemy types defined!"));
		return;
	}

	// Ensure we don't exceed the number of available spawn positions
	int32 ActualSpawnAmount = FMath::Min(collection.MaxSpawnAmount, collection.SpawnPositionList.Num());

	for (int32 i = 0; i < ActualSpawnAmount; i++)
	{
		// Get a random spawn position
		int32 RandomPositionIndex = FMath::RandRange(0, collection.SpawnPositionList.Num() - 1);
		FVector SpawnLocation = collection.SpawnPositionList[RandomPositionIndex]->GetActorLocation();
		FRotator SpawnRotation = collection.SpawnPositionList[RandomPositionIndex]->GetActorRotation();

		// Get a random enemy type
		int32 RandomEnemyIndex = FMath::RandRange(0, collection.EnemiesList.Num() - 1);
		TSubclassOf<AFVEnemyBase> SpawnEnemy = collection.EnemiesList[RandomEnemyIndex];

		// Spawn the enemy
		if (SpawnEnemy)
		{
			AFVEnemyBase* Enemy = GetWorld()->SpawnActor<AFVEnemyBase>(SpawnEnemy, SpawnLocation, SpawnRotation);
			if (Enemy)
			{
				// Optionally, you can perform additional setup on the spawned enemy here
				// For example, setting up AI controllers or perception systems
				AFVEnemyAIController* EnemyController = Cast<AFVEnemyAIController>(Enemy->GetController());
				if (EnemyController)
				{
				   EnemyController->SetupPerception();
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to spawn enemy!"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid enemy class!"));
		}
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

