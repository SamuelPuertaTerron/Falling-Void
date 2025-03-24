// Copyright: Falling Void Studios

#include "Characters/Player/FVPlayerRobot.h"

#include "Characters/Enemies/FVEnemyBase.h"
#include "FVGlobals.h"


void AFVPlayerRobot::Reload(float reloadTime)
{
	if (IsReloading && GetIsDeadOrDowned()) return;

	IsReloading = true;

	GetWorld()->GetTimerManager().SetTimer(m_ReloadTimeHandle, this, &AFVPlayerRobot::ReloadInternal , reloadTime, false);
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
		enemy->OnTakenDamage();

		FVGlobals::LogToScreen("Shot Enemy with name " + enemy->GetName());

		item.Enemy = enemy;
	}
	else
	{
		item.Actor = result.GetActor();
	}

	//Bug: Spawning at (0, 0, 0)
	/*if (result.Location == FVector::Zero())
	{
		item.Location = {-10000, -10000, -10000};
	}
	else
	{
		item.Location = result.Location;
	}*/

	item.Location = result.Location;

	item.Rotation = result.ImpactNormal.ToOrientationRotator();

	OnBulletShot(item);

	CurrentAmmo--;
}

void AFVPlayerRobot::ReloadInternal()
{
	CurrentAmmo = MaxAmmo;
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
