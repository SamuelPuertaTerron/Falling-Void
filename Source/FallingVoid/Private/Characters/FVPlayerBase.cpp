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
	//Ignore negative damage
	if (damage <= 0.0f)
	{
		return;
	}

    float damageToHealth = damage;

	OnTakenDamage();

    // First, apply damage to armor if we have any
    if (Armour > 0)
    {
        float damageToArmor = FMath::Min(Armour, damage);
        Armour -= damageToArmor;
        damageToHealth -= damageToArmor;

        //UE_LOG(LogTemp, Error, TEXT("Taken Armour Damage! Armour remaining: %f"), Armour);
    }

    // Then apply remaining damage to health
    if (damageToHealth > 0)
    {
        float tempDamageReduction = FMath::Max(0.0f, DamageReduction);
        Health -= damageToHealth * DamageReduction;

       // UE_LOG(LogTemp, Error, TEXT("Taken Health Damage! Health remaining: %f"), Health);

        if (Health <= 0.0f)
        {
            OnDied();
        }
    }

	OnTakenDamageLate();
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
