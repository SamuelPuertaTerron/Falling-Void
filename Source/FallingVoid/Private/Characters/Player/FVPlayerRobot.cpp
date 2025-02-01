// Copyright: Falling Void Studios

#include "Characters/Player/FVPlayerRobot.h"

#include "Characters/Enemies/FVEnemyBase.h"

void AFVPlayerRobot::Attack()
{
	//TODO: Add Fire Rate

	FHitResult result = Shoot();

	{
		const AActor* actor = Cast<AActor>(result.GetActor());
		if (actor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Shot Actor with name: %s"), *actor->GetName());
		}
	}

	{
		AFVEnemyBase* enemy = Cast<AFVEnemyBase>(result.GetActor());
		if (enemy)
		{
			enemy->TakeDamage(15.0f);
			UE_LOG(LogTemp, Warning, TEXT("Shot Actor with name: %s"), *enemy->GetName());
		}
	}
}

FHitResult AFVPlayerRobot::Shoot()
{
	FVector location = GetActorLocation();
	FRotator rotation = GetActorRotation();
	FVector endTrace = FVector::ZeroVector;

	const APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	if (playerController)
	{
		playerController->GetPlayerViewPoint(location, rotation);
		endTrace = location + (rotation.Vector() * FireRange);
	}

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(Shoot), true, GetInstigator());
	FHitResult hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(hit, location, endTrace, ECC_Visibility, traceParams);

	return hit;
}
