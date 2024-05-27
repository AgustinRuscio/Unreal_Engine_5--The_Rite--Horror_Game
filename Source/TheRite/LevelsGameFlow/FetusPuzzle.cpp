//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "FetusPuzzle.h"
#include "TheRite/Interactuables/Fetus.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
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
	
	for (auto Element : RegularFetus)
	{
		Element->OnCorrectFetus.AddDynamic(this, &AFetusPuzzle::CheckNextPuzzleStep);
		Element->OnWrongFetus.AddDynamic(this, &AFetusPuzzle::ResetPuzzle);
	}

	TotalPuzzleStps = RegularFetus.Num();

	for (auto Element : PosiblePosition)
	{
		AUXPosiblePosition.Add(Element);
	}

	for (auto Element : RightFetus)
	{
		AUXRightFetus.Add(Element);
	}
	
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
		});
		
		GetWorld()->GetTimerManager().SetTimer(Timer_LightsOn, timerDelegate, OffsetLightsOn, false);
	}
}

void AFetusPuzzle::ResetPuzzle()
{
	LightsOut();

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_WrongInteraction);
	
	bPuzzleActivated = false;
	bFirstInteraction = true;
	RoomDoor->SetLockedState(false);
	
	for (auto Element : RegularFetus)
	{
		Element->ResetFetus();
	}
	for (auto Element : RightFetus)
	{
		Element->ResetFetus();
	}

	AUXRightFetus.Empty();
	for (auto Element : RightFetus)
	{
		AUXRightFetus.Add(Element);
	}
	
	ReLocateFetus();
	
	LightsOn();
}

void AFetusPuzzle::CheckNextPuzzleStep()
{
	LightsOut();

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_CorrectInteraction);

	TotalPuzzleStps++;
	
	TotalPuzzleStps == RegularFetus.Num() ? PuzzleComplete() : NextStep();
}

void AFetusPuzzle::NextStep()
{
	if(bFirstInteraction)
	{
		bFirstInteraction = false;
		
		RoomDoor->SetLockedState(true);
	}
	
	for (auto Element : RegularFetus)
	{
		Element->ResetFetus();
	}

	for (auto Element : RightFetus)
	{
		Element->ResetFetus();
	}
	
	ReLocateFetus();
	
	LightsOn();
}

void AFetusPuzzle::PuzzleComplete()
{
	OnPuzzleComplete.Broadcast();

	for (auto Element : RegularFetus)
	{
		Element->Destroy();
	}

	for (auto Element : RightFetus)
	{
		Element->Destroy();
	}
}

void AFetusPuzzle::ReLocateFetus()
{
	RemoveFirstRightFetus();
	
	for (auto Element : RegularFetus)
	{
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
}