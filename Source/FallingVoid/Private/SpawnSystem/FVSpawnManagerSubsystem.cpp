// Copyright: Falling Void Studios


#include "SpawnSystem/FVSpawnManagerSubsystem.h"

void UFVSpawnManagerSubsystem::SetSpawnManager(AFVSpawnManager* manager)
{
	m_SpawnManager = manager;
}

AFVSpawnManager* UFVSpawnManagerSubsystem::GetSpawnManager() const
{
	return m_SpawnManager;
}

void UFVSpawnManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UFVSpawnManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
