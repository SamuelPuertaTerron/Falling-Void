// Copyright: Falling Void Studios

#include "Characters/Player/FVPlayerRobot.h"

#include "Characters/Enemies/FVEnemyBase.h"
#include <FVGlobals.h>


void AFVPlayerRobot::Attack()
{
	//TODO: Add Fire Rate

	FHitResult result = Shoot();

	{
		const AActor* actor = Cast<AActor>(result.GetActor());
		if (actor)
		{
			FVGlobals::LogToScreen("Shot Actor with name " + actor->GetName());
		}
	}

	{
		AFVEnemyBase* enemy = Cast<AFVEnemyBase>(result.GetActor());
		if (enemy)
		{
			const float damage = BaseDanage * DamageModifier;
			enemy->TakeDamage(damage);

			FVGlobals::LogToScreen("Shot Enemy with name " + enemy->GetName());
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
