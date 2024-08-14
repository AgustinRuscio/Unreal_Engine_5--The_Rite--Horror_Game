//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "AutomaticCloseDoorTrigger.h"
#include "Engine/TriggerVolume.h"
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Characters/Alex.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AAutomaticCloseDoorTrigger::AAutomaticCloseDoorTrigger()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AAutomaticCloseDoorTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	BindTriggers();

	BindTimeLinesMethods();
}

//----------------------------------------------------------------------------------------------------------------------
void AAutomaticCloseDoorTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CloseDoorTimeLine.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Timelines Methods
void AAutomaticCloseDoorTrigger::BindTimeLinesMethods()
{
	FOnTimelineFloat CloseDoorTimeLienTick;
	CloseDoorTimeLienTick.BindUFunction(this, FName(""));
	CloseDoorTimeLine.AddInterpFloat(CloseDoorCurve, CloseDoorTimeLienTick);
	
	FOnTimelineEventStatic FirstTurnOnCallbackFinished;
	FirstTurnOnCallbackFinished.BindUFunction(this, FName("OnTimerFinished"));
	CloseDoorTimeLine.SetTimelineFinishedFunc(FirstTurnOnCallbackFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void AAutomaticCloseDoorTrigger::OnTimerFinished()
{
	if(playerInside) return;

	DoorToClose->AutomaticClose();
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region Collider Methods
void AAutomaticCloseDoorTrigger::BindTriggers()
{
	RoomTrigger->OnActorBeginOverlap.AddDynamic(this, &AAutomaticCloseDoorTrigger::CheckActorIn);
	RoomTrigger->OnActorEndOverlap.AddDynamic(this, &AAutomaticCloseDoorTrigger::CheckActorOut);
}

//----------------------------------------------------------------------------------------------------------------------
void AAutomaticCloseDoorTrigger::CheckActorIn(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor)) return;

	playerInside = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AAutomaticCloseDoorTrigger::CheckActorOut(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!playerInside) return;
	if(!Cast<AAlex>(OtherActor))return;

	playerInside = false;

	CloseDoorTimeLine.PlayFromStart();
}
#pragma endregion