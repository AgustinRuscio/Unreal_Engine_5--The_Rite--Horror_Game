//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "FetusPuzzle.h"
#include "TheRite/Interactuables/Fetus.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/Interactuables/Door.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

AFetusPuzzle::AFetusPuzzle()
{
	PrimaryActorTick.bCanEverTick = true;
}

//---------------- System Class Methods
void AFetusPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	for (auto Element : AllFetus)
	{
		Element->OnInteractionTrigger.AddDynamic(this, &AFetusPuzzle::OnInteraction);
		
		Element->OnCorrectFetus.AddDynamic(this, &AFetusPuzzle::CheckNextPuzzleStep);
		Element->OnWrongFetus.AddDynamic(this, &AFetusPuzzle::ResetPuzzle);
		
		if(Element->GetIsCorrectFetus())
			RightFetus.Add(Element);
		else
			RegularFetus.Add(Element);
	}

	for (auto Element : PosiblePosition)
	{
		AUXPosiblePosition.Add(Element);
	}

	for (auto Element : RightFetus)
	{
		AUXRightFetus.Add(Element);
	}

	if(MaxFetusPerRound > AllFetus.Num() -1)
		MaxFetusPerRound = AllFetus.Num() -1;
	
	ReLocateFetus();
}

void AFetusPuzzle::LightsOut()
{
	for (auto Element : RoomLights)
	{
		Element->TurnOff();
	}
}

void AFetusPuzzle::LightsOn()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(Timer_LightsOn))
	{
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([&]
		{
			for (auto Element : RoomLights)
			{
				Element->TurnOn();
			}

			for (auto Element : AllFetus)
			{
				Element->SetCanInteract(true);
			}
		});
		
		GetWorld()->GetTimerManager().SetTimer(Timer_LightsOn, timerDelegate, OffsetLightsOn, false);
	}
}

void AFetusPuzzle::OnInteraction(AInteractor* interactor)
{
	for (auto Element : AllFetus)
	{
		Element->SetCanInteract(false);
	}
}

void AFetusPuzzle::ResetPuzzle()
{
	LightsOut();

	OffsetLightsOn = SFX_WrongInteraction->GetDuration();
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_WrongInteraction);
	
	bPuzzleActivated = false;
	bFirstInteraction = true;
	RoomDoor->SetLockedState(false);
	
	for (auto Element : AllFetus)
	{
		Element->ResetFetus();
	}

	AUXRightFetus.Empty();
	
	for (auto Element : RightFetus)
	{
		AUXRightFetus.Add(Element);
	}

	TotalPuzzleStps = 0;
	
	ReLocateFetus();
	
	LightsOn();
}

void AFetusPuzzle::CheckNextPuzzleStep()
{
	LightsOut();

	OffsetLightsOn = SFX_CorrectInteraction->GetDuration();
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_CorrectInteraction);

	TotalPuzzleStps++;
	
	TotalPuzzleStps == RightFetus.Num() ? PuzzleComplete() : NextStep();
}

void AFetusPuzzle::NextStep()
{
	if(bFirstInteraction)
	{
		bFirstInteraction = false;
		
		RoomDoor->SetLockedState(true);
		RoomDoor->HardClosing();
	}
	
	for (auto Element : AllFetus)
	{
		Element->ResetFetus();
	}
	
	ReLocateFetus();
	
	LightsOn();
}

void AFetusPuzzle::PuzzleComplete()
{
	OnPuzzleComplete.Broadcast();

	for (auto Element : AllFetus)
	{
		Element->Destroy();
	}

	Destroy();
}

void AFetusPuzzle::ReLocateFetus()
{
	RemoveFirstRightFetus();
	
	int counter = 0;
	
	for (auto Element : RegularFetus)
	{
		if(counter >= MaxFetusPerRound ||AUXPosiblePosition.Num() == 0) break;
		counter++;
		
		auto randomizer = FMath::RandRange(0, AUXPosiblePosition.Num() - 1);
		auto newPos = AUXPosiblePosition[randomizer];
		
		Element->SetActorLocation(newPos->GetActorLocation());
		Element->SetActorRotation(newPos->GetActorRotation());
		
		auto EndAuxTarget = AUXPosiblePosition[AUXPosiblePosition.Num()-1];
		
		AUXPosiblePosition[AUXPosiblePosition.Num()-1] = newPos;
		AUXPosiblePosition[randomizer] = EndAuxTarget;
		
		AUXPosiblePosition.RemoveAt(AUXPosiblePosition.Num()-1);
	}

	AUXPosiblePosition.Empty();
	
	for (auto Element : PosiblePosition)
	{
		AUXPosiblePosition.Add(Element);
	}
}

void AFetusPuzzle::RemoveFirstRightFetus()
{
	auto currentFetus = AUXRightFetus[0];
	
	auto rand = FMath::RandRange(0, AUXPosiblePosition.Num() - 1);
	auto currentTarget = AUXPosiblePosition[rand];
		
	currentFetus->SetActorLocation(currentTarget->GetActorLocation());
	currentFetus->SetActorRotation(currentTarget->GetActorRotation());
		
	auto EndAuxTarget = AUXPosiblePosition[AUXPosiblePosition.Num()-1];
	AUXPosiblePosition[AUXPosiblePosition.Num()-1] = currentTarget;
	AUXPosiblePosition[rand] = EndAuxTarget;
	AUXPosiblePosition.RemoveAt(AUXPosiblePosition.Num()-1);


	auto EndAuxFetus = AUXRightFetus[AUXRightFetus.Num()-1];
	AUXRightFetus[AUXRightFetus.Num()-1] = currentFetus;
	AUXRightFetus[0] = EndAuxFetus;
	AUXRightFetus.RemoveAt(AUXRightFetus.Num()-1);
}