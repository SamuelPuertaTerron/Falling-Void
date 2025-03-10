// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FVSpawnManager.generated.h"

class AFVEnemyBase;

UCLASS()
class FALLINGVOID_API AFVSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFVSpawnManager();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemies();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxSpawnAmount = { 5 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AFVEnemyBase>> EnemiesList = { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> SpawnPositionList = { nullptr };
};
