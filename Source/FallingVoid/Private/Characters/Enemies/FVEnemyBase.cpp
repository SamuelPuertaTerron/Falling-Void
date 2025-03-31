// Copyright: Falling Void Studios


#include "Characters/Enemies/FVEnemyBase.h"

#include "FVEnemyAIController.h"
#include "Characters/FVPlayerBase.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

float AFVEnemyBase::GetDamage() const
{
	return BaseDamage * DamageBoost;
}

void AFVEnemyBase::TakeDamage(float damage)
{
	Health -= damage;
	OnTakenDamage();
	if (Health <= 0.0f)
	{
		OnDied();
	}
}

void AFVEnemyBase::Stun(float delay)
{
	m_pController->SetCanMoveBlackboard(false);
	GetWorldTimerManager().SetTimer(m_SunTimer, this, &AFVEnemyBase::StunEnemy, delay, false);
}

void AFVEnemyBase::StunEnemy() const
{
	m_pController->SetCanMoveBlackboard(true);
}

void AFVEnemyBase::StopMovement() const
{
	AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(GetController());
	controller->StopMovement();
}

void AFVEnemyBase::SetWalkSpeed(float modifier)
{
	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(GetMovementComponent());

	if (modifier == -1.0f)
	{
		movement->MaxWalkSpeed = CacheWalkSpeed * SpeedModifer;
		UE_LOG(LogTemp, Warning, TEXT("Cache Walked Speed: %f"), movement->MaxWalkSpeed);
	}
	else
	{
		movement->MaxWalkSpeed = CacheWalkSpeed * modifier;
	}
}

void AFVEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	m_pController = Cast<AFVEnemyAIController>(GetController());
	m_pController->SetCanMoveBlackboard(true);

	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	CacheWalkSpeed = movement->MaxWalkSpeed;

	SetWalkSpeed();
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

	//GetWorld()->DebugDrawTraceTag;
	FHitResult hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(hit, location, endTrace, ECC_Visibility, traceParams);

	//DrawDebugLine(GetWorld(), location, endTrace, FColor::Red, false, 1.0f);

	return hit; 
}
