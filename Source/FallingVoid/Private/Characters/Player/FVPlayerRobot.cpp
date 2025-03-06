// Copyright: Falling Void Studios

#include "Characters/Player/FVPlayerRobot.h"

#include "Characters/Enemies/FVEnemyBase.h"
#include "FVGlobals.h"


void AFVPlayerRobot::StartReload()
{
	if (IsShielding) return;

	IsReloading = true;

	CurrentAmmo = MaxAmmo;
}

void AFVPlayerRobot::EndReload()
{
	IsReloading = false;
}

void AFVPlayerRobot::StartShooting()
{
	GetWorld()->GetTimerManager().SetTimer(m_TimeBetweenShotsTimeHandle, this, &AFVPlayerRobot::Attack, FireRate, true);
}

void AFVPlayerRobot::EndShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(m_TimeBetweenShotsTimeHandle);
}

void AFVPlayerRobot::Attack()
{
	if (IsReloading || IsShielding || CurrentAmmo <= 0)
	{
		//FVGlobals::LogToScreen("Stopped Shooting");
		EndShooting();
		return;
	}

	//FVGlobals::LogToScreen("Called Attack function: " + FString::FromInt(CurrentAmmo));

	FHitItem item = {};
	FHitResult result = Shoot();

	
	AFVEnemyBase* enemy = Cast<AFVEnemyBase>(result.GetActor());
	if (enemy)
	{
		//Damage Modifier 
		//const float damage = BaseDamage * DamageBoost;
		enemy->TakeDamage(BaseDamage);

		FVGlobals::LogToScreen("Shot Enemy with name " + enemy->GetName());

		item.Enemy = enemy;
	}
	else
	{
		item.Actor = result.GetActor();
	}

	item.Location = result.Location;
	item.Rotation = result.ImpactNormal.ToOrientationRotator();

	OnBulletShot(item);

	CurrentAmmo--;
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
