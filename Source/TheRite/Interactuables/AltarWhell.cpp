//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "AltarWhell.h"
#include "MathUtil.h"
#include "Statuette.h"

AAltarWhell::AAltarWhell()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

void AAltarWhell::MoveTimeLineTick(float deltaSeconds)
{
	auto newRoll = FMathf::Lerp(InteractionRotator.Roll, InteractionRotator.Roll + RotationToAdd, deltaSeconds);
	FRotator newRotator = FRotator(InteractionRotator.Pitch, InteractionRotator.Yaw, newRoll);


	auto newStatuetteRoll = FMathf::Lerp(StatuateRotator.Yaw, StatuateRotator.Yaw + RotationToAdd, deltaSeconds);
	FRotator newStatuetteRotator = FRotator(StatuateRotator.Pitch, newStatuetteRoll, StatuateRotator.Roll);

	SetActorRotation(newRotator);
	Statuette->SetActorRotation(newStatuetteRotator);
}

void AAltarWhell::MoveTimeLineFinisehd()
{
	bCanInteract = true;
}

void AAltarWhell::DisableInteraction()
{
	bCanInteract = false;
}

void AAltarWhell::ASignValues(AStatuette* statuette, float desiredRotation, float rotationToAdd)
{
	Statuette = statuette;
	DesiredRotation = desiredRotation;
	RotationToAdd = rotationToAdd;
}


void AAltarWhell::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("MoveTimeLineTick"));
	MoveTimeLine.AddInterpFloat(CurveFloat, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("MoveTimeLineFinisehd"));
	MoveTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

void AAltarWhell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveTimeLine.TickTimeline(DeltaTime);
}

void AAltarWhell::Interaction()
{
	if(!bCanInteract) return;
	
	bCanInteract = false;
	InteractionRotator = GetActorRotation();
	StatuateRotator = Statuette->GetActorRotation();
	
	MoveTimeLine.PlayFromStart();
}

bool AAltarWhell::CheckRotation()
{
	float actualRoll = GetActorRotation().Roll;
	
	if(actualRoll == DesiredRotation) return true;
	

	return false;
}


void AAltarWhell::EnableInteraction()
{
	bCanInteract = true;
}