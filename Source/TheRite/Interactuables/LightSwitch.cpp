//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "LightSwitch.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "Kismet/GameplayStatics.h"

//*****************************Public************************************************
//***********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
ALightSwitch::ALightSwitch()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	WallBlockModel = CreateDefaultSubobject<UStaticMeshComponent>("Wall model");
	SwitchModel = CreateDefaultSubobject<UStaticMeshComponent>("Switch Model");

	SwitchModel->SetupAttachment(WallBlockModel);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightSwitch::Interaction()
{
	if(!bAnimReady || !bCanInteract) return;

	if(bOneUse)
	{
		if(bOneUseReady)
			return;
	}

	bAnimReady = false;

	if(!bOneUse)
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), AudioToPlay, GetActorLocation());
	
	if(bEspecial)
	{
		SwitchTimeLine.PlayFromStart();
		
		return;
	}
	
	if(bFlipFlop)
	{
		for (auto Element : LightToInteract)
		{
			Element->IsLightOn() ? Element->TurnOff() : Element->TurnOn();
		}
		
		SwitchTimeLine.PlayFromStart();
		bFlipFlop = false;
		
		UE_LOG(LogTemp, Warning, TEXT("Flip"));
	}
	else
	{
		for (auto Element : LightToInteract)
		{
			Element->IsLightOn() ? Element->TurnOff() : Element->TurnOn();
		}
		
		SwitchTimeLine.ReverseFromEnd();
		bFlipFlop = true;

		UE_LOG(LogTemp, Warning, TEXT("Flop"));
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALightSwitch::SetSpecialReady()
{
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("SwitchTimeLineTick"));
	SwitchTimeLine.AddInterpFloat(InvertedCurve, CameraTargetTick);
	
	bEspecial = false;
	bOneUse = true;
}

//*****************************Private***********************************************
//***********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	BindTimeLine();
}

//----------------------------------------------------------------------------------------------------------------------
void ALightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SwitchTimeLine.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region TimeLine Methods
void ALightSwitch::BindTimeLine()
{
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("SwitchTimeLineTick"));
	SwitchTimeLine.AddInterpFloat(EmptyCurve, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("SwitchTimeLineFinished"));
	SwitchTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void ALightSwitch::SwitchTimeLineTick(float time)
{
	float lerpValue;

	if(bEspecial)
		lerpValue =  FMath::Lerp(45, -45, time);
	else
		lerpValue =  bFlipFlop ? FMath::Lerp(45, -45, time) : FMath::Lerp(-45, 45, time);
	
	SwitchModel->SetRelativeRotation(FRotator(0, 0, lerpValue));
}

//----------------------------------------------------------------------------------------------------------------------
void ALightSwitch::SwitchTimeLineFinished()
{
	bAnimReady = true;
	
	
	if(!bOneUse) return;
	
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), AudioToPlay, GetActorLocation());
	
	bOneUseReady = true;
	bCanInteract = false;
	OnInteractionTrigger.Broadcast(this);
}
#pragma endregion