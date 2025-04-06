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

    float damageToArmor = FMath::Max(damage * ArmorAbsorptionRatio, MinArmorDamage);
    float damageToHealth = FMath::Max(damage * (1.0f - ArmorAbsorptionRatio), MinHealthDamage);

    float totalDamage = damageToArmor + damageToHealth;
    if (totalDamage > damage)
    {
        float correctionFactor = damage / totalDamage;
        damageToArmor *= correctionFactor;
        damageToHealth *= correctionFactor;
    }

    // Apply armor damage first
    if (Armour > 0.0f)
    {
        float actualArmorDamage = FMath::Min(damageToArmor, Armour);
        Armour -= actualArmorDamage;

        // Reduce health damage by the proportion of armor damage that was absorbed
        if (damageToArmor > 0.0f)
        {
            damageToHealth *= (actualArmorDamage / damageToArmor);
        }

        UE_LOG(LogTemp, Warning, TEXT("Armor damaged by %.1f (remaining: %.1f)"), actualArmorDamage, Armour);
    }

    // Apply remaining damage to health
    if (damageToHealth > 0.0f)
    {
        // Apply damage reduction if needed
        float finalHealthDamage = damageToHealth * FMath::Max(0.0f, DamageReduction);
        Health -= finalHealthDamage;

        UE_LOG(LogTemp, Warning, TEXT("Health damaged by %.1f (remaining: %.1f)"), finalHealthDamage, Health);

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
