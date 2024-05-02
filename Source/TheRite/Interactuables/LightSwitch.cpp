//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "LightSwitch.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "Kismet/GameplayStatics.h"

ALightSwitch::ALightSwitch()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	WallBlockModel = CreateDefaultSubobject<UStaticMeshComponent>("Wall model");
	SwitchModel = CreateDefaultSubobject<UStaticMeshComponent>("Switch Model");

	SwitchModel->SetupAttachment(WallBlockModel);
}

//---------------- System Class Methods
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	BindTimeLine();
}

void ALightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SwitchTimeLine.TickTimeline(DeltaTime);
}

void ALightSwitch::Interaction()
{
	if(!bAnimReady) return;
	
	Super::Interaction();
	
	bAnimReady = false;

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), AudioToPlay, GetActorLocation());
	
	if(bFlipFlop)
	{
		bFlipFlop = false;
		SwitchTimeLine.PlayFromStart();
		
		for (auto Element : LightToInteract)
		{
			Element->IsLightOn() ? Element->TurnOff() : Element->TurnOn();
		}
	}
	else
	{
		bFlipFlop = true;
		SwitchTimeLine.ReverseFromEnd();
		
		for (auto Element : LightToInteract)
		{
			Element->IsLightOn() ? Element->TurnOff() : Element->TurnOn();
		}
	}
}

//---------------- TimeLine Methods
void ALightSwitch::BindTimeLine()
{
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("SwitchTimeLineTick"));
	SwitchTimeLine.AddInterpFloat(EmptyCurve, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("SwitchTimeLineFinished"));
	SwitchTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

void ALightSwitch::SwitchTimeLineTick(float time)
{
	float lerpValue;

	lerpValue =  bFlipFlop ? FMath::Lerp(45, -45, time) : FMath::Lerp(-45, 45, time);
	
	SwitchModel->SetRelativeRotation(FRotator(0, 0, lerpValue));
}

void ALightSwitch::SwitchTimeLineFinished()
{
	bAnimReady = true;
}