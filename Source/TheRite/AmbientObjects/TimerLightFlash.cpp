//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "TimerLightFlash.h"
#include <Components/BoxComponent.h>
#include <Components/LightComponent.h>
#include <Engine/Light.h>

//----------------------------------------------------------------------------------------------------------------------
ATimerLightFlash::ATimerLightFlash() : bFlipFlop(false), bLoop(false), bTurnOffOnPlayerOutside(true), Rate(3.f), LightIntensity(4.f)
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Box Component");
	RootComponent = TriggerBox;
}

//----------------------------------------------------------------------------------------------------------------------
void ATimerLightFlash::BeginPlay()
{
	Super::BeginPlay();

	for (auto current : Lights)
	{
		current->GetLightComponent()->SetIntensity(0.f);
	}

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATimerLightFlash::OnPlayerInside);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ATimerLightFlash::OnPlayerOutside);
}

//----------------------------------------------------------------------------------------------------------------------
void ATimerLightFlash::InterpLight()
{
	bFlipFlop = !bFlipFlop;

	for (auto current : Lights)
	{
		current->GetLightComponent()->SetIntensity(bFlipFlop ? LightIntensity : 0.f);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ATimerLightFlash::OnPlayerInside(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!Cast<APawn>(OtherActor)) return;

	if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATimerLightFlash::InterpLight, Rate, bLoop);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ATimerLightFlash::OnPlayerOutside(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bTurnOffOnPlayerOutside) return;
	if (!Cast<APawn>(OtherActor)) return;

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	bFlipFlop = false;

	for (auto current : Lights)
	{
		current->GetLightComponent()->SetIntensity(bFlipFlop ? LightIntensity : 0.f);
	}
}