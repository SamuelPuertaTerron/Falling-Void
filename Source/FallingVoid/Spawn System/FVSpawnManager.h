// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FVSpawnManager.generated.h"

class AFVEnemyBase;

USTRUCT(Blueprintable)
struct FSpawnCollection
{
	GENERATED_BODY()

	//Only set if it has hit the enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxSpawnAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AFVEnemyBase>> EnemiesList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> SpawnPositionList;
};

UCLASS()
class FALLINGVOID_API AFVSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFVSpawnManager();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemies(const FSpawnCollection& collection);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
