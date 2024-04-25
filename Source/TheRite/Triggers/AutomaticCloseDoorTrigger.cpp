//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "AutomaticCloseDoorTrigger.h"
#include "Engine/TriggerVolume.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Characters/Alex.h"

AAutomaticCloseDoorTrigger::AAutomaticCloseDoorTrigger()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AAutomaticCloseDoorTrigger::BeginPlay()
{
	Super::BeginPlay();
	RoomTrigger->OnActorBeginOverlap.AddDynamic(this, &AAutomaticCloseDoorTrigger::CheckActorIn);
	RoomTrigger->OnActorEndOverlap.AddDynamic(this, &AAutomaticCloseDoorTrigger::CheckActorOut);

	FOnTimelineFloat CloseDoorTimeLienTick;
	CloseDoorTimeLienTick.BindUFunction(this, FName(""));
	CloseDoorTimeLine.AddInterpFloat(CloseDoorCurve, CloseDoorTimeLienTick);
	
	FOnTimelineEventStatic FirstTurnOnCallbackFinished;
	FirstTurnOnCallbackFinished.BindUFunction(this, FName("OnTimerFinished"));
	CloseDoorTimeLine.SetTimelineFinishedFunc(FirstTurnOnCallbackFinished);
}

void AAutomaticCloseDoorTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CloseDoorTimeLine.TickTimeline(DeltaTime);
}

void AAutomaticCloseDoorTrigger::CheckActorIn(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor)) return;

	playerInside = true;
}

void AAutomaticCloseDoorTrigger::CheckActorOut(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!playerInside) return;
	if(!Cast<AAlex>(OtherActor))return;

	playerInside = false;

	CloseDoorTimeLine.PlayFromStart();
}

void AAutomaticCloseDoorTrigger::OnTimerFinished()
{
	if(playerInside) return;

	DoorToClose->AutomaticClose();
}