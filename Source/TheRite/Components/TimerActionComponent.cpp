//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "TimerActionComponent.h"

UTimerActionComponent::UTimerActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTimerActionComponent::RunTimer(float deltaTime)
{
	Timer += deltaTime;

	if(Timer < CD) return;

	if(bShowLighterOff)
	{
		bShowLighterOff = false;
		TimerReach.Broadcast();
	}
}

void UTimerActionComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UTimerActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RunTimer(DeltaTime);
}

void UTimerActionComponent::ActionFinished()
{
	bShowLighterOff = true;
	Timer = 0;
}