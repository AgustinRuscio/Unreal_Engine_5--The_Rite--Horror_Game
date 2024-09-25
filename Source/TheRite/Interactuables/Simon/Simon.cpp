//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "Simon.h"

#include "Kismet/GameplayStatics.h"


static FVector CenterEndLocation;

//----------------------------------------------------------------------------------------------------------------------
ASimon::ASimon()
{
	PrimaryActorTick.bCanEverTick = true;

	SimonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Simon Mesh");
	
	CenterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Center Mesh");
	CenterMesh->SetupAttachment(SimonMesh);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::Interaction()
{
	if(!bCanInteract) return;

	Super::Interaction();

	bCanInteract = false;
	StartSequence();
	ChangeButtonsInteractionState(false);
}

//----------------------------------------------------------------------------------------------------------------------
bool ASimon::HasSequenceFinish()
{
	return SequenceCurrentIndex >= CurrenSequence.Num();
}

//----------------------------------------------------------------------------------------------------------------------
bool ASimon::CheckCompleteSequence()
{
	return CheckCountIndex >= CurrenSequence.Num();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::BeginPlay()
{
	Super::BeginPlay();

	CenterEndLocation = CenterMesh->GetComponentLocation() + CenterLocationToAdd;
	
	BindTimeLine();

	for (auto Element : SimonButtons)
	{
		Element->OnInteractionStart.AddDynamic(this, &ASimon::OnButtonPressed);
		Element->OnInteractionFinished.AddDynamic(this, &ASimon::OnButtonPressedFinished);
		Element->Deactivate();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveCenterTimeline.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(GetWorld())
	{
		GetWorldTimerManager().ClearTimer(RePlaySequenceTimerHandle);
	}

	if(RePlaySequenceTimerDelegate.IsBound())
	{
		RePlaySequenceTimerDelegate.Unbind();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::Deactivate()
{
	Super::Deactivate();

	SimonMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	CenterMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::CreateSequence()
{
	CurrenSequence.Empty();
	int8 CheckedIndex = SequenceLevel + 2;

	while (CheckedIndex)
	{
		int8 currentValue = FMath::RandRange(0, 3);
		CurrenSequence.Add(currentValue);

		--CheckedIndex;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::StartSequence()
{
	bIsShowingCurrentSequence = true;
	bReEnableButtons		  =  true;
	SequenceCurrentIndex	  = 0;

	ChangeButtonsInteractionState(false);

	CreateSequence();

	PlaySequence(CurrenSequence[SequenceCurrentIndex]);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::PlaySequence(int8 PlayedIndex)
{
	SimonButtons[PlayedIndex]->PressForced();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::ShowNextSequence()
{
	SequenceCurrentIndex++;

	if(HasSequenceFinish())
	{
		bIsShowingCurrentSequence = false;
		ChangeButtonsInteractionState(true);
	}
	else
	{
		PlaySequence(CurrenSequence[SequenceCurrentIndex]);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::ChangeSequenceLevel()
{
	ClearGameVariables();
	
	SequenceLevel++;
	
	if(SequenceLevel >= LevelQuantity)
	{
		SimonCompleted();
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SFX_NextLevelReach, GetActorLocation());
		ShowSequenceTimerRate = SFX_NextLevelReach->Duration;
		
		PlayShowSequenceTimerHandle();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::ClearGameVariables()
{
	SequenceCurrentIndex = 0;
	CheckCountIndex		 = 0;
	CurrenSequence.Empty();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::ChangeButtonsInteractionState(bool NewState)
{
	for (auto Element : SimonButtons)
	{
		if (NewState)
			Element->Activate();
		else
			Element->Deactivate();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::OnButtonPressed(int8 ColorPressed)
{
	for (auto Element : SimonButtons)
	{
		Element->Deactivate();
	}

	if(ColorPressed == CurrenSequence[CheckCountIndex])
	{	
		CheckCountIndex++;
		
		if(CheckCompleteSequence())
			ChangeSequenceLevel();
	}
	else
	{
		Failure();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::OnButtonPressedFinished()
{
	if(bSimonCompleted)
	{
		Deactivate();
		ChangeButtonsInteractionState(false);
	}
	else
	{
		if(bIsShowingCurrentSequence)
		{
			ShowNextSequence();
		}
		else
		{
			ChangeButtonsInteractionState(bReEnableButtons);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::SimonCompleted()
{
	bSimonCompleted = true;
	
	Deactivate();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SFX_SimonCompleted, GetActorLocation());
	
	ChangeButtonsInteractionState(false);
	
	MoveCenterTimeline.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::Failure()
{
	ClearGameVariables();
	ChangeButtonsInteractionState(false);

	SequenceLevel	 = 0;
	bReEnableButtons = false;
	
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SFX_Failure, GetActorLocation());
	bCanInteract = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::PlayShowSequenceTimerHandle()
{
	if(GetWorld())
	{
		if(!GetWorldTimerManager().IsTimerActive(RePlaySequenceTimerHandle))
		{
			GetWorldTimerManager().SetTimer(RePlaySequenceTimerHandle, RePlaySequenceTimerDelegate, ShowSequenceTimerRate, false);
		}
	}
}

#pragma region Bind TimeLine
//----------------------------------------------------------------------------------------------------------------------
void ASimon::BindTimeLine()
{
	FOnTimelineFloat MoveCenterTick;
	MoveCenterTick.BindUFunction(this, FName("MoveCenterTick"));
	MoveCenterTimeline.AddInterpFloat(MoveCenterCurve, MoveCenterTick);
	
	FOnTimelineEventStatic MoveCenterFinished;
	MoveCenterFinished.BindUFunction(this, FName("MoveCenterFinished"));
	MoveCenterTimeline.SetTimelineFinishedFunc(MoveCenterFinished);

	RePlaySequenceTimerDelegate.BindLambda([&]
	{
		StartSequence();
	});
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::MoveCenterTick(float deltaSeconds)
{
	auto lerpLocation = FMath::Lerp(CenterMesh->GetComponentLocation(), CenterEndLocation, deltaSeconds);
	
	CenterMesh->SetWorldLocation(lerpLocation);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::MoveCenterFinished()
{
	SimonMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CenterMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
#pragma endregion