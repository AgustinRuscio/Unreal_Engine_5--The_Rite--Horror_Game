#include "Clock.h"


AClock::AClock()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("ClockBase");
	Needles = CreateDefaultSubobject<UStaticMeshComponent>("Needles");
	
	RootComponent = BaseMesh;

	Needles->SetupAttachment(BaseMesh);

	Light= CreateDefaultSubobject<UPointLightComponent>("Light");
}

void AClock::Interaction()
{
	ClockReady();
}

void AClock::BeginPlay()
{
	Super::BeginPlay();
	AudioToPlay = Sound;
}

void AClock::ClockReady()
{
	TheRite->SetClockReady();
	TheRite->OnClockGain.Broadcast();
	Destroy();
}
