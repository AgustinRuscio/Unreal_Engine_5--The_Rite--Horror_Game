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

bool AAltarWhell::CheckRotation()
{
	float actualRoll = Statuette->GetRotation().Yaw;
	
	return  actualRoll == DesiredRotation;
}

//---------------- System Class Methods
void AAltarWhell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveTimeLine.TickTimeline(DeltaTime);
}

void AAltarWhell::BeginPlay()
{
	Super::BeginPlay();

	BindTimeLines();
}

void AAltarWhell::Interaction()
{
	if(!bCanInteract || !bStatuette) return;
	
	bCanInteract = false;
	InteractionRotator = GetActorRotation();
	StatuateRotator = Statuette->GetActorRotation();
	
	MoveTimeLine.PlayFromStart();
}

//---------------- States Methods
void AAltarWhell::EnableInteraction()
{
	bCanInteract = true;
}

void AAltarWhell::DisableInteraction()
{
	bCanInteract = false;
}
void AAltarWhell::StatuetteReady()
{
	bStatuette = true;
}

void AAltarWhell::ASignValues(AStatuette* statuette, float desiredRotation, float rotationToAdd)
{
	Statuette = statuette;
	DesiredRotation = desiredRotation;
	RotationToAdd = rotationToAdd;
}

//---------------- TimeLines Methods
void AAltarWhell::BindTimeLines()
{
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("MoveTimeLineTick"));
	MoveTimeLine.AddInterpFloat(CurveFloat, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("MoveTimeLineFinisehd"));
	MoveTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

void AAltarWhell::MoveTimeLineTick(float deltaSeconds)
{
	auto newPich = FMathf::Lerp(InteractionRotator.Pitch, InteractionRotator.Pitch + RotationToAdd, deltaSeconds);


	auto newStatuetteYaw = FMathf::Lerp(StatuateRotator.Yaw, StatuateRotator.Yaw + RotationToAdd, deltaSeconds);
	FRotator newStatuetteRotator = FRotator(StatuateRotator.Pitch, newStatuetteYaw, StatuateRotator.Roll);

	SetActorRotation(FRotator(newPich, InteractionRotator.Yaw,  InteractionRotator.Roll));
	Statuette->SetActorRotation(newStatuetteRotator);
}

void AAltarWhell::MoveTimeLineFinisehd()
{
	bCanInteract = true;
}