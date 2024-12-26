//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "Coffin.h"
#include <Kismet/GameplayStatics.h>

//----------------------------------------------------------------------------------------------------------------------
ACoffin::ACoffin() : bFlipFlop(true)
{
 	PrimaryActorTick.bCanEverTick = true;

	CoffinMesh = CreateDefaultSubobject<UStaticMeshComponent>("Coffin Mesh");
	RootComponent = CoffinMesh;
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::OpenCoffin()
{
	bOpened = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::BeginPlay()
{
	Super::BeginPlay();

	//------- Coffin Movement timeline
	FOnTimelineFloat MovementTimelineCallback;
	MovementTimelineCallback.BindUFunction(this, FName("CoffinMovementTimeLineTick"));
	CoffinMovementTimeLine.AddInterpFloat(TimeLineCurveFloat, MovementTimelineCallback);

	FOnTimelineEventStatic MovementTimelineFinishedCallback;
	MovementTimelineFinishedCallback.BindUFunction(this, FName("CoffinMovementTimeLineFinished"));
	CoffinMovementTimeLine.SetTimelineFinishedFunc(MovementTimelineFinishedCallback);


	//------- Coffin Closed timeline
	FOnTimelineFloat ClosedTimelineCallback;
	ClosedTimelineCallback.BindUFunction(this, FName("CoffinClosedTimeLineTick"));
	CoffinClosedMovementTimeLine.AddInterpFloat(TimeLineCloseCurveFloat, ClosedTimelineCallback);

	FOnTimelineEventStatic ClosedTimelineFinishedCallback;
	ClosedTimelineFinishedCallback.BindUFunction(this, FName("CoffinClosedTimeLineFinished"));
	CoffinClosedMovementTimeLine.SetTimelineFinishedFunc(ClosedTimelineFinishedCallback);


	CoffinOriginalLocation = GetActorLocation();

	CoffinOpenedLocation = CoffinOriginalLocation + LocationToAddOpen;
	CoffinClosedLocation = CoffinOriginalLocation + LocationToAddClosed;
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CoffinMovementTimeLine.TickTimeline(DeltaTime);
	CoffinClosedMovementTimeLine.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::Interaction()
{
	if (!bCanInteract) return;

	if (bOpened)
	{
		bCanInteract = false;

		OnInteractionTrigger.Broadcast(this);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OpeningSound, GetActorLocation());

		if(bFlipFlop)
			CoffinMovementTimeLine.PlayFromStart();
		else
			CoffinMovementTimeLine.ReverseFromEnd();
	}
	else
	{
		CoffinClosedMovementTimeLine.PlayFromStart();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ForceSound, GetActorLocation());
		bCanInteract = false;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::CoffinMovementTimeLineTick(float tick)
{
	auto lerpedLocation = FMath::Lerp(CoffinOriginalLocation, CoffinOpenedLocation, tick);

	SetActorLocation(lerpedLocation);
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::CoffinMovementTimeLineFinished()
{
	bCanInteract = true;
	bFlipFlop = !bFlipFlop;
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::CoffinClosedTimeLineTick(float tick)
{
	auto lerpedLocation = FMath::Lerp(CoffinOriginalLocation, CoffinClosedLocation, tick);

	SetActorLocation(lerpedLocation);
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::CoffinClosedTimeLineFinished()
{
	bCanInteract = true;
}