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
	
	BigClockMesh = CreateDefaultSubobject<UStaticMeshComponent>("Clock Mesh");
	
	HourNeedleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Hour needle Mesh");
	MinuturesNeedleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Minutes Needle Mesh");
	CenterMesh= CreateDefaultSubobject<UStaticMeshComponent>("Center Mesh");
	
	HourNeedleMesh->SetupAttachment(BigClockMesh);
	MinuturesNeedleMesh->SetupAttachment(BigClockMesh);
	CenterMesh->SetupAttachment(BigClockMesh);
	
	AllNeedles.Add(CenterMesh);
	AllNeedles.Add(HourNeedleMesh);
	AllNeedles.Add(MinuturesNeedleMesh);
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

	CurrentSelected = AllNeedles[CurrentNeedle];
	AllNeedles[CurrentNeedle]->SetMaterial(0, SelectedNeedleMaterial);

	Player->OnFocusMode(NewCameraPosition->GetActorLocation(), NewCameraPosition->GetActorRotation());
	
	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetFocusInput();

	controller->OnPrevInventoryItem.AddDynamic(this, &ABigClock::PrevNeedle);
	controller->OnNextInventoryItem.AddDynamic(this, &ABigClock::NextNeedle);
	controller->OnInteractionPressed.AddDynamic(this, &ABigClock::NeedleInteraction);
	controller->OnLeaveFocus.AddDynamic(this, &ABigClock::LeaveFocus);
	
	bIsFocus = true;
}

void ABigClock::SetReadyToUse()
{
	bReadyToUse = true;
}

void ABigClock::LeaveFocus()
{
	if(!bCanInteract || TimeLineMooving) return;
	
	bIsFocus = false;
	Player->BackToNormalView();

	AllNeedles[CurrentNeedle]->SetMaterial(0, NeedlebaseMaterial);
	
	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetNormalInput();

	controller->OnPrevInventoryItem.RemoveDynamic(this, &ABigClock::PrevNeedle);
	controller->OnNextInventoryItem.RemoveDynamic(this, &ABigClock::NextNeedle);
	controller->OnInteractionPressed.RemoveDynamic(this, &ABigClock::NeedleInteraction);
	controller->OnLeaveFocus.RemoveDynamic(this, &ABigClock::LeaveFocus);
}

void ABigClock::PrevNeedle()
{
	if(TimeLineMooving)return;
	
	AllNeedles[CurrentNeedle]->SetMaterial(0, NeedlebaseMaterial);
	
	CurrentNeedle--;

	if(CurrentNeedle < 0)
		CurrentNeedle = AllNeedles.Num()-1;

	ChangeNeedle();
}

void ABigClock::NextNeedle()
{
	if(TimeLineMooving)return;
	
	AllNeedles[CurrentNeedle]->SetMaterial(0, NeedlebaseMaterial);
	
	CurrentNeedle++;

	if(CurrentNeedle >= AllNeedles.Num())
		CurrentNeedle = 0;
	
	ChangeNeedle();
}

void ABigClock::NeedleInteraction()
{
	if(TimeLineMooving) return;
	
	if(AllNeedles[CurrentNeedle] == CenterMesh)
	{
		CheckNeedlesPosition();
	}
	else
	{
		TimeLineMooving = true;

		if(EndNeedleRotation == FRotator(16,04,03))
		{
			InitialNeedleRotation = AllNeedles[CurrentNeedle]->GetComponentRotation();
			EndNeedleRotation = InitialNeedleRotation + RotationToAdd;
		}
		else
		{
			InitialNeedleRotation = EndNeedleRotation;
			EndNeedleRotation = InitialNeedleRotation + RotationToAdd;
		}

		MoveNeedleTimeLine.PlayFromStart();
	}
}

void ABigClock::ChangeNeedle()
{
	CurrentSelected = AllNeedles[CurrentNeedle];
	EndNeedleRotation = FRotator(16,04,03);
	AllNeedles[CurrentNeedle]->SetMaterial(0, SelectedNeedleMaterial);
}

void ABigClock::CheckNeedlesPosition()
{
	UE_LOG(LogTemp, Warning, TEXT("Testeo"));
	UE_LOG(LogTemp, Warning, TEXT("Minutes Pitch: %f   Desired  %f"), MinuturesNeedleMesh->GetComponentRotation().Pitch, DesireMinutesRotation);
	UE_LOG(LogTemp, Warning, TEXT("Hours Pitch: %f   Desired  %f"), HourNeedleMesh->GetComponentRotation().Pitch, DesireHourRotation);

	if(!bReadyToUse)
	{
		Player->ForceTalk(AudioToPlay);
		return;
	}
	
	if(MinuturesNeedleMesh->GetComponentRotation().Pitch !=  DesireMinutesRotation ||
		HourNeedleMesh->GetComponentRotation().Pitch !=  DesireHourRotation) return;

	OnClockPuzzleCompleted.Broadcast();
	LeaveFocus();
	UE_LOG(LogTemp, Warning, TEXT("Es"));
	
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
	auto newPitch = FMath::Lerp(InitialNeedleRotation, EndNeedleRotation, deltaTime);

	AllNeedles[CurrentNeedle]->SetWorldRotation(newPitch);
}

void ABigClock::MoveNeedleTimeLineFinished()
{
	if(EndNeedleRotation.Pitch == 360)
		EndNeedleRotation = FRotator(0,EndNeedleRotation.Yaw, EndNeedleRotation.Roll);
			
	TimeLineMooving = false;
}