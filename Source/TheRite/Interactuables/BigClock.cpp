//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "BigClock.h"

#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Characters/Alex.h"

#define PRINTONVIEWPORT(X) GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT(X)));


//--------------------- System Class methods
ABigClock::ABigClock()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BigClockMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	//HourNeedleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	//MinuturesNeedleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	//HourNeedleMesh->SetupAttachment(BigClockMesh);
	//MinuturesNeedleMesh->SetupAttachment(BigClockMesh);


	MinutesPointLight = CreateDefaultSubobject<UPointLightComponent>("Minutes light");
	HoursPointLight = CreateDefaultSubobject<UPointLightComponent>("Hour light");
	CenterPointLight = CreateDefaultSubobject<UPointLightComponent>("Center light");


	//MinutesPointLight ->SetupAttachment(MinuturesNeedleMesh);
	//HoursPointLight->SetupAttachment(HourNeedleMesh);
}

void ABigClock::BeginPlay()
{
	Super::BeginPlay();
	
	Player = CastChecked<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	BindTimeLine();
}

void ABigClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveNeedleTimeLine.TickTimeline(DeltaTime);
}

void ABigClock::Interaction()
{
	Super::Interaction();

	if(bIsFocus || !bCanInteract) return;

	if(bReadyToUse)
	{
		Player->ForceTalk(AudioToPlay);
		return;
	}

	bIsFocus = true;
	Player->OnFocusMode(NewCameraPosition->GetActorLocation(), NewCameraPosition->GetActorRotation());

	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetFocusInput();

	controller->OnPrevInventoryItem.RemoveDynamic(this, &ABigClock::PrevNeedle);
	controller->OnNextInventoryItem.RemoveDynamic(this, &ABigClock::NextNeedle);
	controller->OnInteractionPressed.RemoveDynamic(this, &ABigClock::NeedleInteraction);
	controller->OnLeaveFocus.RemoveDynamic(this, &ABigClock::LeaveFocus);
}

void ABigClock::SetReadyToUse()
{
	bReadyToUse = true;
}

void ABigClock::LeaveFocus()
{
	if(!bCanInteract) return;
	
	bIsFocus = false;
	Player->BackToNormalView();
	
	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetNormalInput();

	controller->OnPrevInventoryItem.RemoveDynamic(this, &ABigClock::PrevNeedle);
	controller->OnNextInventoryItem.RemoveDynamic(this, &ABigClock::NextNeedle);
	controller->OnInteractionPressed.RemoveDynamic(this, &ABigClock::NeedleInteraction);
	controller->OnLeaveFocus.RemoveDynamic(this, &ABigClock::LeaveFocus);
}

void ABigClock::PrevNeedle()
{
	CurrentNeedle--;

	if(CurrentNeedle < 0)
		CurrentNeedle = 3;

	
}

void ABigClock::NextNeedle()
{
	CurrentNeedle++;

	if(CurrentNeedle > 3)
		CurrentNeedle = 0;

	
}

void ABigClock::NeedleInteraction()
{
	
}

void ABigClock::CheckNeedlesPosition()
{
	
}

//--------------------- TimeLine methods
void ABigClock::BindTimeLine()
{
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("MoveNeedleTimeLineTick"));
	MoveNeedleTimeLine.AddInterpFloat(CurveFloat, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("MoveNeedleTimeLineFinished"));
	MoveNeedleTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

void ABigClock::MoveNeedleTimeLineTick(float deltaTime)
{
}

void ABigClock::MoveNeedleTimeLineFinished()
{
}
