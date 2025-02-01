// Copyright: Falling Void Studios


#include "Characters/Enemies/FVEnemyBase.h"

#include "Characters/FVPlayerBase.h"

void AFVEnemyBase::Attack()
{
	FHitResult result = Shoot();

	{
		AFVPlayerBase* player = Cast<AFVPlayerBase>(result.GetActor());
		if (player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Shot Actor with name: %s"), *player->GetName());
			player->TakeDamage(25.0f);
		}
	}
}

FHitResult AFVEnemyBase::Shoot()
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
