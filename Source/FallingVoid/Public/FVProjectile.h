// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FVProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class AFVPlayerBase;

UCLASS()
class FALLINGVOID_API AFVProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFVProjectile();

	//Sets the damages to the damage of the enemy that has shot it
	void SetDamage(float damage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Damage{ 10.0f };
	//This can only be set in the inspector and should be used inside the event graph
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float LifeSpan{ 5.0f };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
