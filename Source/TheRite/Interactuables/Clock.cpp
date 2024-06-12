//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Clock.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

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


void AClock::Interaction()
{
	Super::Interaction();
	
	OnInteractionTrigger.Broadcast(this);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_GrabItem, GetActorLocation());
	Destroy();
}

FName AClock::GetObjectData()
{
	return NextLevelName;
}