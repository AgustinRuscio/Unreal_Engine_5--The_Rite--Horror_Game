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
	Super::Interaction();

	
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
		Element->SetCanInteract(false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveCenterTimeline.TickTimeline(DeltaTime);
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
void ASimon::StarSequence()
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
		//Dispatcher
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
		Element->SetCanInteract(NewState);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::OnButtonPressed(int8 ColorPressed)
{
	for (auto Element : SimonButtons)
	{
		Element->SetCanInteract(false);
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
	for (auto Element : SimonButtons)
	{
		Element->SetCanInteract(true);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimon::SimonCompleted()
{
	bCanInteract = false;
	
	for (auto Element : SimonButtons)
	{
		Element->Deactivate();
	}
	
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

	if(bIsShowingCurrentSequence)
	{
		ShowNextSequence();
	}
	else
	{
		ChangeButtonsInteractionState(bReEnableButtons);
	}
}
#pragma endregion