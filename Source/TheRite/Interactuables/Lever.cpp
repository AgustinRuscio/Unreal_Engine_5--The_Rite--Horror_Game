//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "Lever.h"

#include "FrameTypes.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
ALever::ALever() : bIsCorrect(false),  bWasUsed(false), bPlayForward(false)
{
	PrimaryActorTick.bCanEverTick = true;

	LeverBaseMesh	  = CreateDefaultSubobject<UStaticMeshComponent>("Base lever mesh");
	RootComponent = LeverBaseMesh;

	LeverMesh	  = CreateDefaultSubobject<UStaticMeshComponent>("Lever Mesh");
	LeverMesh->SetupAttachment(LeverBaseMesh);
	
	bCanInteract = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ALever::Interaction()
{
	if(!bCanInteract) return;
	bCanInteract = false;
	
	bWasUsed = true;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SFX_GrabItem, GetActorLocation());
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
	LeverMesh->SetRelativeRotation(InitialRotation);
	
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
	auto lerpedRot = FMath::Lerp(InitialRotation, UsedRotation, delta);
	
	LeverMesh->SetRelativeRotation(lerpedRot);
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