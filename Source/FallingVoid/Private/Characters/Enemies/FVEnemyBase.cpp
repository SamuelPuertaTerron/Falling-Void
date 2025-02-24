// Copyright: Falling Void Studios


#include "Characters/Enemies/FVEnemyBase.h"

#include "Characters/FVPlayerBase.h"

#include "FVGlobals.h"
#include "Characters/Player/FVPlayerRobot.h"

void AFVEnemyBase::Attack()
{
	FHitResult result = Shoot();

	AFVPlayerRobot* playerRobot = Cast<AFVPlayerRobot>(result.GetActor());
	if (playerRobot)
	{
		FVGlobals::LogToScreen("Hit Player with name: " + playerRobot->GetName());

		//TODO: Make sure that the enemy hits the shield
		if (!playerRobot->IsShielding)
		{
			const float damage = BaseDamage * DamageBoost * playerRobot->DamageReduction;
			playerRobot->TakeDamage(damage);
		}
	}

	/*if (AFVPlayerSamurai* playerSamurai = Cast<AFVPlayerSamurai>(result.GetActor()))
	{
		const float damage = BaseDamage * DamageBoost * playerSamurai->DamageReduction;
		playerSamurai->TakeDamage(damage);
	}*/
}

FHitResult AFVEnemyBase::Shoot()
{
	FVector location = GetActorLocation();
	FRotator rotation = GetActorRotation();
	FVector endTrace = FVector::ZeroVector;

	const APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	if (playerController)
	{
		endTrace = location + (rotation.Vector() * FireRange);
	}

	FName traceTag("EnemyShoot");

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(Shoot), true, GetInstigator());
	traceParams.TraceTag = traceTag;

	GetWorld()->DebugDrawTraceTag;
	FHitResult hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(hit, location, endTrace, ECC_Visibility, traceParams);

	DrawDebugLine(GetWorld(), location, endTrace, FColor::Red, false, 1.0f);

	return hit;
}
