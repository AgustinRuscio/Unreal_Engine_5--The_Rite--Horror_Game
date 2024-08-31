//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Clock.h"
#include "Components/PointLightComponent.h"
#include "Engine/PointLight.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------
AClock::~AClock()
{
	OnInteractionTrigger.Clear();
}

//----------------------------------------------------------------------------------------------------------------------
FName AClock::GetObjectData() const
{
	return NextLevelName;
}

//----------------------------------------------------------------------------------------------------------------------
void AClock::Interaction()
{
	if(bTest)
	{
		for (auto Element : TurnedOfLights)
		{
			Element->TurnOff();
		}
	}
	else
	{
		Super::Interaction();
		
		OnInteractionTrigger.Broadcast(this);
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_GrabItem, GetActorLocation());
		Destroy();
	}
}