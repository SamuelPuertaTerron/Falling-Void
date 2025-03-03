// Copyright: Falling Void Studios


#include "Characters/Enemies/FVEnemyBase.h"

#include "Characters/FVPlayerBase.h"

#include "FVGlobals.h"
#include "Characters/Player/FVPlayerRobot.h"

float AFVEnemyBase::GetDamage()
{
	return BaseDamage * DamageBoost;
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
