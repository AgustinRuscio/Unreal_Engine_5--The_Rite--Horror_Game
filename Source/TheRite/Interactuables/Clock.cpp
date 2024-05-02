//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Clock.h"
#include "Components/PointLightComponent.h"

AClock::AClock()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("ClockBase");
	Needles = CreateDefaultSubobject<UStaticMeshComponent>("Needles");
	
	RootComponent = BaseMesh;

	Needles->SetupAttachment(BaseMesh);

	Light= CreateDefaultSubobject<UPointLightComponent>("Light");
	Light->SetupAttachment(BaseMesh);
}

AClock::~AClock()
{
	OnInteractionTrigger.Clear();
}

void AClock::BeginPlay()
{
	Super::BeginPlay();
	AudioToPlay = Sound;
}

void AClock::Interaction()
{
	OnInteractionTrigger.Broadcast(this);

	Destroy();
}

FName AClock::GetObjectData()
{
	return NextLevelName;
}