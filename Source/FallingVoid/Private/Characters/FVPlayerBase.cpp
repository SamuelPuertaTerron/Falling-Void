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

void AFVPlayerBase::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("AFVPlayerBase::Attack() called"));

	//Super::Attack();
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

bool AFVPlayerBase::NodeGetIsDeadOrDowned() const
{
	return GetIsDeadOrDowned();
}

bool AFVPlayerBase::NodeGetIsAlive() const
{
	return GetIsAlive();
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
