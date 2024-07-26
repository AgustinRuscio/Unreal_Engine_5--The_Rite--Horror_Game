//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "BigClock.h"
#include "Blueprint/UserWidget.h"
#include "TheRite/Widgets/TutorialWidget.h"
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
	ClockPendulum = CreateDefaultSubobject<UStaticMeshComponent>("Pendulum Mesh");
	
	HourNeedleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Hour needle Mesh");
	MinuturesNeedleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Minutes Needle Mesh");
	
	HourNeedleMesh->SetupAttachment(BigClockMesh);
	MinuturesNeedleMesh->SetupAttachment(BigClockMesh);
	ClockPendulum->SetupAttachment(BigClockMesh);

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
	if(bIsFocus || !bCanInteract) return;
	
	CurrentSelected = AllNeedles[CurrentNeedle];
	AllNeedles[CurrentNeedle]->SetMaterial(0, SelectedNeedleMaterial);

	Player->OnFocusMode(NewCameraPosition->GetActorTransform(), ExittingRotation);
	
	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetFocusInput();

	controller->OnPrevInventoryItem.AddDynamic(this, &ABigClock::PrevNeedle);
	controller->OnNextInventoryItem.AddDynamic(this, &ABigClock::NextNeedle);
	controller->OnInteractionPressed.AddDynamic(this, &ABigClock::NeedleInteraction);
	controller->OnLeaveFocus.AddDynamic(this, &ABigClock::LeaveFocus);
	
	bIsFocus = true;

	if(bFirstInteraction && bShowClue)
	{
		bFirstInteraction = false;

		Widget_ClockClue = CreateWidget<UTutorialWidget>(GetWorld(), WG_ClockClue);
		Widget_ClockClue->AddToViewport(0);
		Widget_ClockClue->SetVisibility(ESlateVisibility::Visible);
		Widget_ClockClue->SetIsFocusable(true);

		UGameplayStatics::SpawnSound2D(GetWorld(), SFX_Clue);
		
		if(!GetWorld()->GetTimerManager().IsTimerActive(Timer_ClockClue))
		{

			FTimerDelegate OnTimePass;

			OnTimePass.BindLambda([&]
			{
				Widget_ClockClue->RemoveFromParent();
			});
			
			GetWorld()->GetTimerManager().SetTimer(Timer_ClockClue, OnTimePass, 5.f, false);
		}
	}	
	//CheckNeedlesPosition();
}

void ABigClock::SetReadyToUse()
{
	bReadyToUse = true;
}

void ABigClock::LeaveFocus()
{
	if(!bCanInteract || TimeLineMoving || Player->GetFocusingState()) return;
	
	bIsFocus = false;
	Player->BackToNormalView(NewCameraPosition->GetActorTransform(), ExittingVector, ExittingRotation);

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
	if(TimeLineMoving || Player->GetFocusingState()) return;
	
	AllNeedles[CurrentNeedle]->SetMaterial(0, NeedlebaseMaterial);
	
	CurrentNeedle--;

	if(CurrentNeedle < 0)
		CurrentNeedle = AllNeedles.Num()-1;

	ChangeNeedle();
}

void ABigClock::NextNeedle()
{
	if(TimeLineMoving || Player->GetFocusingState()) return;
	
	AllNeedles[CurrentNeedle]->SetMaterial(0, NeedlebaseMaterial);
	
	CurrentNeedle++;

	if(CurrentNeedle >= AllNeedles.Num())
		CurrentNeedle = 0;
	
	ChangeNeedle();
}

void ABigClock::NeedleInteraction()
{
	if(TimeLineMoving || Player->GetFocusingState() || !bCanInteract) return;
	
		TimeLineMoving = true;
		
		if(EndNeedleRotation == FRotator(16,04,03))
		{
			auto bIsMinute = AllNeedles[CurrentNeedle] == MinuturesNeedleMesh;
			
			if(bIsMinute)
			{
				if(LastMinutesRot == FRotator(16,04,03))
				{
					InitialNeedleRotation = AllNeedles[CurrentNeedle]->GetComponentRotation();
					EndNeedleRotation = InitialNeedleRotation + RotationToAdd;
				}
				else
				{
					InitialNeedleRotation = LastMinutesRot;
					EndNeedleRotation = InitialNeedleRotation + RotationToAdd;
				}
			}
			else
			{
				if(LastHourRot == FRotator(16,04,03))
				{
					InitialNeedleRotation = AllNeedles[CurrentNeedle]->GetComponentRotation();
					EndNeedleRotation = InitialNeedleRotation + RotationToAdd;
				}
				else
				{
					InitialNeedleRotation = LastHourRot;
					EndNeedleRotation = InitialNeedleRotation + RotationToAdd;
				}
			}
			
			MoveNeedleTimeLine.PlayFromStart();

			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_NeeddleMoving, GetActorLocation());
		}
		else
		{
			InitialNeedleRotation = EndNeedleRotation;
			EndNeedleRotation = InitialNeedleRotation + RotationToAdd;
			
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_NeeddleMoving, GetActorLocation());
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
	if(!bReadyToUse)
		return;
	
	const float Tolerance = 0.001f;
	
	if (FMath::Abs(MinuturesNeedleMesh->GetComponentRotation().Pitch - DesireMinutesRotation) > Tolerance ||
		FMath::Abs(HourNeedleMesh->GetComponentRotation().Pitch - DesireHourRotation) > Tolerance)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_ClockLocked,GetActorLocation());
		
		return;
	}
	
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_PuzzleComplete, GetActorLocation());
	
	OnClockPuzzleCompleted.Broadcast();
	LeaveFocus();
	
	bCanInteract = false;
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

	
	AllNeedles[CurrentNeedle] == MinuturesNeedleMesh ?
		LastMinutesRot = EndNeedleRotation :
		LastHourRot = EndNeedleRotation;
	
	TimeLineMoving = false;
	
	CheckNeedlesPosition();
}