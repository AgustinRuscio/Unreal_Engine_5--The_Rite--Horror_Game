//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "Lever.h"
#include "Components/PointLightComponent.h"

//----------------------------------------------------------------------------------------------------------------------
ALever::ALever() : bIsCorrect(false),  bWasUsed(false), bPlayForward(false)
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh	  = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;

	PointLight = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	PointLight->SetupAttachment(StaticMesh);

	bCanInteract = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ALever::Interaction()
{
	if(!bCanInteract) return;
	bCanInteract = false;
	
	bWasUsed = true;

	bPlayForward = true;
	OnLeverUsageStart.Broadcast(this);
	Timeline.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void ALever::ResetLever()
{
	//if(bCanInteract) return;
	if(!bWasUsed) return;
	
	bPlayForward = false;
	OnLeverUsageStart.Broadcast(this);
	Timeline.ReverseFromEnd();
}

//----------------------------------------------------------------------------------------------------------------------
void ALever::BeginPlay()
{
	Super::BeginPlay();
	PointLight->SetIntensity(0.f);
	
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
	PointLight->SetIntensity(delta * 100);
}

//----------------------------------------------------------------------------------------------------------------------
void ALever::LeverTimeLineFinished()
{
	OnLeverUsageEnd.Broadcast(this);
	
	if(bPlayForward)
		OnInteractionTrigger.Broadcast(this);
	else
	{
		if(!bWasUsed) return;
		bCanInteract = true;
		bWasUsed = false;
	}
}