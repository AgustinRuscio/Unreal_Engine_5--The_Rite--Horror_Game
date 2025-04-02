//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "PressableButton.h"

//----------------------------------------------------------------------------------------------------------------------
APressableButton::APressableButton()
{
 	PrimaryActorTick.bCanEverTick = true;

	Mesh		  = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

//----------------------------------------------------------------------------------------------------------------------
void APressableButton::Interaction()
{
    if(!bCanInteract) return;
    bCanInteract = false;
    OnInteractionTrigger.Broadcast(this);
	ButtonTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void APressableButton::BeginPlay()
{
	Super::BeginPlay();

	originalLocation = GetActorLocation();
	endLocation = originalLocation + LocationToAdd;

	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("ButtonPressedTick"));
	ButtonTimeLine.AddInterpFloat(ButtonPressedCurveFloat, CameraTargetTick);

	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("ButtonPressedFinished"));
	ButtonTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);

}

//----------------------------------------------------------------------------------------------------------------------
void APressableButton::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ButtonTimeLine.TickTimeline(DeltaSeconds);
}

//----------------------------------------------------------------------------------------------------------------------
void APressableButton::ButtonPressedTick(float deltaSeconds)
{
	auto lerped = FMath::Lerp(originalLocation, endLocation, deltaSeconds);
	SetActorLocation(lerped);
}

//----------------------------------------------------------------------------------------------------------------------
void APressableButton::ButtonPressedFinished()
{
	bCanInteract = true;
}