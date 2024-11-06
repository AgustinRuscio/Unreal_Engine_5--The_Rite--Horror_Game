//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "Lever.h"

#include "Components/PointLightComponent.h"

//----------------------------------------------------------------------------------------------------------------------
ALever::ALever()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh	  = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;

	PointLight = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	PointLight->SetupAttachment(StaticMesh);
}

//----------------------------------------------------------------------------------------------------------------------
void ALever::Interaction()
{
	if(!bCanInteract) return;
	Super::Interaction();
	
	Timeline.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void ALever::BeginPlay()
{
	Super::BeginPlay();
	PointLight->Intensity = 0;

	FOnTimelineFloat LeverTimeLienTick;
	LeverTimeLienTick.BindUFunction(this, FName("LeverTimeLineTick"));
	Timeline.AddInterpFloat(CurveFloat, LeverTimeLienTick);
	
	FOnTimelineEventStatic LeverTimeLineFinished;
	LeverTimeLineFinished.BindUFunction(this, FName("LeverTimeLineFinished"));
	Timeline.SetTimelineFinishedFunc(LeverTimeLineFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void ALever::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Timeline.TickTimeline(DeltaSeconds);
}

//----------------------------------------------------------------------------------------------------------------------
void ALever::LeverTimeLineTick(float delta)
{
	PointLight->Intensity = delta * 100;
}

//----------------------------------------------------------------------------------------------------------------------
void ALever::LeverTimeLineFinished()
{
	
}

//----------------------------------------------------------------------------------------------------------------------
void ALever::ResetLever()
{
	Timeline.ReverseFromEnd();
}