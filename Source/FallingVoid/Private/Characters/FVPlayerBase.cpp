// Copyright: Falling Void Studios


#include "Characters/FVPlayerBase.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"


// Sets default values
AFVPlayerBase::AFVPlayerBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupStimuliSource();
}

// Called when the game starts or when spawned
void AFVPlayerBase::BeginPlay()
{
	Super::BeginPlay();

}

bool AFVPlayerBase::GetIsDeadOrDowned() const
{
	return PlayerHealthState == EPlayerHealthState::Dead || PlayerHealthState == EPlayerHealthState::Downed;
}

bool AFVPlayerBase::GetIsAlive() const
{
	return PlayerHealthState == EPlayerHealthState::Alive;
}

void AFVPlayerBase::SetInteractionState(const EPlayerInteractionState& state)
{
	m_CurrentInteractionState = state;
}

EPlayerInteractionState AFVPlayerBase::GetInteractionState() const
{
	return m_CurrentInteractionState;
}

bool AFVPlayerBase::NodeGetIsDeadOrDowned() const
{
	return GetIsDeadOrDowned();
}

bool AFVPlayerBase::NodeGetIsAlive() const
{
	return GetIsAlive();
}

void AFVPlayerBase::TakeDamage(float damage)
{
	float currDamage = damage;

	if(Armour >= currDamage)
	{
		Armour -= currDamage;
	}
	else if (currDamage > 0 && Armour <= 0) 
	{
		//Note: Fixed negative damage. 
		float tempDamageReduction = DamageReduction;
		Health -= currDamage * FMath::Clamp(tempDamageReduction, 0.0f, FLT_MAX);
		Armour = 0;
	}
	else
	{
		//Note: Fixed negative damage. 
		float tempDamageReduction = DamageReduction;
		Health -= damage * FMath::Clamp(tempDamageReduction, 0.0f, FLT_MAX);

		if (Health <= 0.0f)
		{
			OnDied();
		}
	}
}

// Called every frame
void AFVPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFVPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFVPlayerBase::SetupStimuliSource()
{
	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimuli Source"));
	if (StimuliSource)
	{
		StimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSource->RegisterWithPerceptionSystem();
	}
}
