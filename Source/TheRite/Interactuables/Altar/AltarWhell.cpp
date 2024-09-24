//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "AltarWhell.h"
#include "MathUtil.h"
#include "Statuette.h"
#include "Kismet/GameplayStatics.h"

//*****************************Public********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AAltarWhell::AAltarWhell()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

//----------------------------------------------------------------------------------------------------------------------
bool AAltarWhell::CheckRotation()
{
	float actualRoll = Statuette->GetRotation().Yaw;
	
	return  actualRoll == DesiredRotation;
}

//----------------------------------------------------------------------------------------------------------------------
void AAltarWhell::Interaction()
{
	if(!bCanInteract || !bStatuette) return;
	
	bCanInteract = false;
	InteractionRotator = GetActorRotation();
	StatuateRotator = Statuette->GetActorRotation();

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_Rotation, GetActorLocation());
	MoveTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region States Methods
void AAltarWhell::EnableInteraction()
{
	bCanInteract = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AAltarWhell::DisableInteraction()
{
	bCanInteract = false;
}

//----------------------------------------------------------------------------------------------------------------------
void AAltarWhell::StatuetteReady()
{
	bStatuette = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AAltarWhell::ASignValues(AStatuette* statuette, float desiredRotation, float rotationToAdd)
{
	Statuette = statuette;
	DesiredRotation = desiredRotation;
	RotationToAdd = rotationToAdd;
}
#pragma endregion 

//*****************************Private********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AAltarWhell::BeginPlay()
{
	Super::BeginPlay();

	BindTimeLines();
}

//----------------------------------------------------------------------------------------------------------------------
void AAltarWhell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveTimeLine.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region TimeLines Methods
void AAltarWhell::BindTimeLines()
{
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("MoveTimeLineTick"));
	MoveTimeLine.AddInterpFloat(CurveFloat, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("MoveTimeLineFinished"));
	MoveTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void AAltarWhell::MoveTimeLineTick(float deltaSeconds)
{
	auto newPich = FMathf::Lerp(InteractionRotator.Pitch, InteractionRotator.Pitch + RotationToAdd, deltaSeconds);

	auto newStatuetteYaw = FMathf::Lerp(StatuateRotator.Yaw, StatuateRotator.Yaw + RotationToAdd, deltaSeconds);
	FRotator newStatuetteRotator = FRotator(StatuateRotator.Pitch, newStatuetteYaw, StatuateRotator.Roll);

	SetActorRotation(FRotator(newPich, InteractionRotator.Yaw,  InteractionRotator.Roll));
	Statuette->SetActorRotation(newStatuetteRotator);
}

//----------------------------------------------------------------------------------------------------------------------
void AAltarWhell::MoveTimeLineFinished()
{
	bCanInteract = true;
}
#pragma endregion 