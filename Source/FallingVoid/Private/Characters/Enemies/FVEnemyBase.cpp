// Copyright: Falling Void Studios


#include "Characters/Enemies/FVEnemyBase.h"

#include "Characters/FVPlayerBase.h"

#include "FVGlobals.h"

void AFVEnemyBase::Attack()
{
	FHitResult result = Shoot();

	{
		AFVPlayerBase* player = Cast<AFVPlayerBase>(result.GetActor());
		if (player)
		{
			FVGlobals::LogToScreen("Hit Player with name: " + player->GetName());

			const float damage = BaseDanage * DamageModifier;

			player->TakeDamage(damage);
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
