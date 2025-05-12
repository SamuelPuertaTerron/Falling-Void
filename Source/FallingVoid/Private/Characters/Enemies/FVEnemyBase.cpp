// Copyright: Falling Void Studios


#include "Characters/Enemies/FVEnemyBase.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "FVEnemyAIController.h"
#include "Characters/FVPlayerBase.h"

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
	if (!m_pController || !IsValid(m_pController))
	{
		UE_LOG(LogTemp, Error, TEXT("Controller is null or invalid!"));
		return;
	}

	m_pController->SetIsStunned(true);
	m_pController->StopMovement();

	TWeakObjectPtr<AFVEnemyBase> thisWeak = this;
	GetWorldTimerManager().SetTimer(m_SunTimer, [thisWeak]()
		{
			if (thisWeak.IsValid() && thisWeak->m_pController && IsValid(thisWeak->m_pController))
			{
				thisWeak->m_pController->SetIsStunned(false);
			}
		}, delay, false);
}

void AFVEnemyBase::StopMovement() const
{
	AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(GetController());
	controller->StopMovement();
}

void AFVEnemyBase::SetWalkSpeed(float modifier)
{
	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(GetMovementComponent());

}

void AFVEnemyBase::SetCapsuleCollision() const
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block); // Block other pawns
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block); // Block dynamic objects
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore); // Ignore physics objects if not needed
}

void AFVEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	m_pController = Cast<AFVEnemyAIController>(GetController());
	if (!m_pController || !IsValid(m_pController))
	{
		UE_LOG(LogTemp, Error, TEXT("Controller is null or invalid!"));
		return;
	}

	m_pController->SetIsStunned(false);

	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	CacheWalkSpeed = movement->MaxWalkSpeed;

	//SetWalkSpeed();
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
