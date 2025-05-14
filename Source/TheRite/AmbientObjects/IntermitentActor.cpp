//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "IntermitentActor.h"
#include "CustomLight.h"
#include "GameFramework/Actor.h"
#include "LightsTheRite.h"
#include <Kismet/GameplayStatics.h>


//----------------------------------------------------------------------------------------------------------------------
AIntermitentActor::AIntermitentActor() : bShouldTurnLightsOffBefore(true), bShouldTurnLightsOnAfter(true), IntermitentTimeOn(0.5f), IntermitentTimeOff(0.3f)
{
	PrimaryActorTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
void AIntermitentActor::ActivateIntermitent()
{
	ToggleLights(bShouldTurnLightsOffBefore);

	ToggleActorsVisibility(false);

	if(GetWorld()->GetTimerManager().IsTimerActive(IntermitentTimerOn)) return;
	GetWorld()->GetTimerManager().SetTimer(IntermitentTimerOn, IntermitentDelegateOn, IntermitentTimeOn, false);

}

//----------------------------------------------------------------------------------------------------------------------
void AIntermitentActor::BeginPlay()
{
	Super::BeginPlay();

	IntermitentDelegateOn.BindLambda([this]()
		{
			ToggleLights(true);

			for (auto current : SFX)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), current, GetActorLocation());
			}

			if (GetWorld()->GetTimerManager().IsTimerActive(IntermitentTimerOff)) return;
			GetWorld()->GetTimerManager().SetTimer(IntermitentTimerOff, IntermitentDelegateOff, IntermitentTimeOff, false);
		});

	IntermitentDelegateOff.BindLambda([this]()
		{
			ToggleLights(bShouldTurnLightsOnAfter);
			ToggleActorsVisibility(true);
		});
	
}

//----------------------------------------------------------------------------------------------------------------------
void AIntermitentActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (GetWorld()->GetTimerManager().IsTimerActive(IntermitentTimerOn))
		GetWorld()->GetTimerManager().ClearTimer(IntermitentTimerOn);

	if (GetWorld()->GetTimerManager().IsTimerActive(IntermitentTimerOff))
		GetWorld()->GetTimerManager().ClearTimer(IntermitentTimerOff);

	IntermitentDelegateOn.Unbind();
	IntermitentDelegateOff.Unbind();
}

//----------------------------------------------------------------------------------------------------------------------
void AIntermitentActor::ToggleLights(bool active)
{
	for (auto current : Lights)
	{
		active ? current->TurnOn() : current->TurnOff();
	}
	for (auto current : CustomLights)
	{
		active ? current->TurnOn() : current->TurnOff();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AIntermitentActor::ToggleActorsVisibility(bool hidden)
{
	for (auto current : IntermitentActors)
	{
		current->SetActorHiddenInGame(hidden);
	}
}