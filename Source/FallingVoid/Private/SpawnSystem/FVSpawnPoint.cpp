// Copyright: Falling Void Studios


#include "SpawnSystem/FVSpawnPoint.h"

#include "SpawnSystem/FVSpawnManager.h"
#include "SpawnSystem/FVSpawnManagerSubsystem.h"

// Sets default values
AFVSpawnPoint::AFVSpawnPoint()
{
 	// Only call Tick() when debug is on.
	PrimaryActorTick.bCanEverTick = IsDebug;

}

void AFVSpawnPoint::Tick(float DeltaSeconds)
{
	if (IsDebug)
	{
		static auto spawnManager = GetGameInstance()->GetSubsystem<UFVSpawnManagerSubsystem>()->GetSpawnManager();

		DrawDebugSphere(GetWorld(), GetActorLocation(), spawnManager->GetSpawnRadius(), 12, FColor::Red);
	}
}
