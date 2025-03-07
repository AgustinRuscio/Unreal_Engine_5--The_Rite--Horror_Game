//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "Coffin.h"
#include <Kismet/GameplayStatics.h>
#include <Components/ArrowComponent.h>

//----------------------------------------------------------------------------------------------------------------------
ACoffin::ACoffin() : bFlipFlop(true), bWasForceOpen(false)
{
 	PrimaryActorTick.bCanEverTick = true;

	CoffinMCenter = CreateDefaultSubobject<USceneComponent>("Coffin Center");
	RootComponent = CoffinMCenter;
	
	CoffinMattress = CreateDefaultSubobject<UStaticMeshComponent>("CoffinM Mattress");
	CoffinMattress->SetupAttachment(CoffinMCenter);

	CoffinDoor = CreateDefaultSubobject<UStaticMeshComponent>("Coffin Mesh");
	CoffinDoor->SetupAttachment(CoffinMCenter);
	
	CoffinLatch = CreateDefaultSubobject<UStaticMeshComponent>("Coffin Latch");
	CoffinLatch->SetupAttachment(CoffinDoor);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Body Mesh");
	BodyMesh->SetupAttachment(CoffinMattress);

	InsideActorLocation = CreateDefaultSubobject<UArrowComponent>("Arrow Location");
	InsideActorLocation->SetupAttachment(CoffinMattress);
}

//----------------------------------------------------------------------------------------------------------------------
bool ACoffin::IsCoffinOpen() const
{
	return bIsOpen;
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::UnlockCoffin()
{ 
	bOpened = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::ForceCoffinOpenning()
{
	bWasForceOpen = true;
	CoffinMovementTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::BeginPlay()
{
	Super::BeginPlay();

	BindTimeLineMethods();

	SaveLocationAndRotation();

	if (InisdeActor.Num() > 0)
	{
		int index = 0;
		for (auto current : InisdeActor)
		{
			current->AttachToComponent(InsideActorLocation, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			current->SetActorRotation(RotatorsInside[index]);
			current->SetActorLocation(current->GetActorLocation() + LocationInside[index]);

			index++;
		}
	}
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
		bWasForceOpen = false;
		bCanInteract = false;
		
		CoffinOpening.Broadcast();

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OpeningSound, GetActorLocation());

		bIsOpen = bFlipFlop;

		if (bFlipFlop)
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
void ACoffin::BindTimeLineMethods()
{
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
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::SaveLocationAndRotation()
{
	CoffinOriginalRotation = CoffinDoor->GetRelativeRotation();
	CoffinOpenedRotation = CoffinOriginalRotation + RotationToAddOpen;
	CoffinClosedRotation = CoffinOriginalRotation + RotationToAddClosed;


	CoffinLatchOriginalRotation = CoffinLatch->GetRelativeRotation();
	CoffinLatchOpenedRotation = CoffinLatchOriginalRotation + RotationLatchToAddOpen;
	CoffinLatchClosedRotation = CoffinLatchOriginalRotation + RotationLatchToAddClosed;


	CoffinMattressOriginalRotation = CoffinMattress->GetRelativeLocation();
	CoffinMattressOpenedRotation = CoffinMattressOriginalRotation + LocationToAddMatrresOpen;
	CoffinMattressClosedRotation = CoffinMattressOriginalRotation + LocationToAddMatrresClosed;
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::CoffinMovementTimeLineTick(float tick)
{
	auto lerpedDoorLocation = FMath::Lerp(CoffinOriginalRotation, CoffinOpenedRotation, tick);
	auto lerpedLatchLocation = FMath::Lerp(CoffinLatchOriginalRotation, CoffinLatchOpenedRotation, tick);
	auto lerpedMattresLocation = FMath::Lerp(CoffinMattressOriginalRotation, CoffinMattressOpenedRotation, tick * .8f);

	LerpValues(lerpedDoorLocation, lerpedLatchLocation, lerpedMattresLocation);
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::CoffinMovementTimeLineFinished()
{
	if (bWasForceOpen) return;

	bCanInteract = true;
	OnInteractionTrigger.Broadcast(this);
	bFlipFlop = !bFlipFlop;
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::CoffinClosedTimeLineTick(float tick)
{
	auto lerpedDoorLocation = FMath::Lerp(CoffinOriginalRotation, CoffinClosedRotation, tick);
	auto lerpedLatchLocation = FMath::Lerp(CoffinLatchOriginalRotation, CoffinLatchClosedRotation, tick);
	auto lerpedMattresLocation = FMath::Lerp(CoffinMattressOriginalRotation, CoffinMattressClosedRotation, tick * 0.8f);

	LerpValues(lerpedDoorLocation, lerpedLatchLocation, lerpedMattresLocation);
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::CoffinClosedTimeLineFinished()
{
	bCanInteract = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ACoffin::LerpValues(const FRotator& DoorRotation, const FRotator& LatchRotation, const FVector& MattressLocation)
{
	CoffinMattress->SetRelativeLocation(MattressLocation);
	CoffinDoor->SetRelativeRotation(DoorRotation);
	CoffinLatch->SetRelativeRotation(LatchRotation);
}