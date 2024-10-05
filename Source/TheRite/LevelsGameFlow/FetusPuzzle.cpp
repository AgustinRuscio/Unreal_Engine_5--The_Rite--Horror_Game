//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "FetusPuzzle.h"
#include "TheRite/Interactuables/Fetus.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
AFetusPuzzle::AFetusPuzzle()
{
	PrimaryActorTick.bCanEverTick = true;

	bActive			   = false;
	bFirstInteraction  = true;
	MaxObjectsPerRound = 8;
	Player			   = nullptr;

	SFX_CorrectInteraction	= nullptr;
	SFX_WrongInteraction	= nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
bool AFetusPuzzle::IsActive() const
{
	return bActive;
}

//----------------------------------------------------------------------------------------------------------------------
void AFetusPuzzle::SetPuzzleState(bool NewPuzzleState)
{
	bActive = NewPuzzleState;
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void AFetusPuzzle::BeginPlay()
{
	if(!bActive)
		return
	
	Super::BeginPlay();

	Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
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
//----- New objects
	for (auto Element : RegularObjects)
	{
		
	}
	for (auto Element : CorrectObjects)
	{
		
	}
//------
	
	for (auto Element : PossiblePosition)
	{
		AUXPossiblePosition.Add(Element);
	}

	for (auto Element : RightFetus)
	{
		AUXRightFetus.Add(Element);
	}

	if(MaxObjectsPerRound > AllFetus.Num() -1)
		MaxObjectsPerRound = AllFetus.Num() -1;
	
	ReLocateObjects();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetusPuzzle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(LightsOn_TimerHandle);
	LightsOn_TimerDelegate.Unbind();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetusPuzzle::OnInteraction(AInteractor* interactable)
{
	Player->ForceLighterOff();
	Player->SetPlayerOptions(false, false, false);
	
	for (auto Element : AllFetus)
	{
		Element->SetCanInteract(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
#pragma region Lights Manipulation Methods
void AFetusPuzzle::LightsOut()
{
	for (auto Element : AllLights)
	{
		Element->TurnOff();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AFetusPuzzle::LightsOn()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(LightsOn_TimerHandle))
	{
		LightsOn_TimerDelegate.BindLambda([&]
		{
			for (auto Element : AllLights)
			{
				Element->TurnOn();
			}

			for (auto Element : AllFetus)
			{
				Element->SetCanInteract(true);
			}
			
			//Player->SetPlayerOptions(false, true, false);
		});
		
		GetWorld()->GetTimerManager().SetTimer(LightsOn_TimerHandle, LightsOn_TimerDelegate, OffsetLightsOn, false);
	}
}
#pragma endregion

//----------------------------------------------------------------------------------------------------------------------
#pragma region Puzzle Steps
void AFetusPuzzle::ResetPuzzle()
{
	LightsOut();

	OffsetLightsOn = SFX_WrongInteraction->GetDuration();
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_WrongInteraction);
	
	bFirstInteraction = true;
	
	for (auto Element : AllFetus)
	{
		Element->ResetFetus();
	}

	AUXRightFetus.Empty();
	
	for (auto Element : RightFetus)
	{
		AUXRightFetus.Add(Element);
	}

	TotalPuzzleSteps = 0;
	
	ReLocateObjects();
	
	LightsOn();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetusPuzzle::CheckNextPuzzleStep()
{
	LightsOut();

	OffsetLightsOn = SFX_CorrectInteraction->GetDuration();
	
	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_CorrectInteraction);

	TotalPuzzleSteps++;
	
	TotalPuzzleSteps == RightFetus.Num() ? PuzzleComplete() : NextStep();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetusPuzzle::NextStep()
{
	if(bFirstInteraction)
	{
		bFirstInteraction = false;
	}
	
	for (auto Element : AllFetus)
	{
		Element->ResetFetus();
	}
	
	ReLocateObjects();
	
	LightsOn();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetusPuzzle::PuzzleComplete()
{
	OnPuzzleComplete.Broadcast();

	for (auto Element : AllFetus)
	{
		Element->Destroy();
	}

	for (auto Element : RegularObjects)
	{
		Element->Destroy();
	}

	for (auto Element : CorrectObjects)
	{
		Element->Destroy();
	}

	LightsOn_TimerDelegate.Unbind();
	GetWorldTimerManager().ClearTimer(LightsOn_TimerHandle);

	//Player->SetPlayerOptions(false, true, false);

	Destroy();
}

//----------------------------------------------------------------------------------------------------------------------
void AFetusPuzzle::ReLocateObjects()
{
	RemoveFirstRightObjects();
	
	int counter = 0;
	
	for (auto Element : RegularFetus)
	{
		if(counter >= MaxObjectsPerRound ||AUXPossiblePosition.Num() == 0) break;
		counter++;
		
		auto randomizer = FMath::RandRange(0, AUXPossiblePosition.Num() - 1);
		auto newPos = AUXPossiblePosition[randomizer];
		
		Element->SetActorLocation(newPos->GetActorLocation());
		Element->SetActorRotation(newPos->GetActorRotation() + FRotator(0,-90,0));
		
		auto EndAuxTarget = AUXPossiblePosition[AUXPossiblePosition.Num()-1];
		
		AUXPossiblePosition[AUXPossiblePosition.Num()-1] = newPos;
		AUXPossiblePosition[randomizer] = EndAuxTarget;
		
		AUXPossiblePosition.RemoveAt(AUXPossiblePosition.Num()-1);
	}

	AUXPossiblePosition.Empty();
	
	for (auto Element : PossiblePosition)
	{
		AUXPossiblePosition.Add(Element);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AFetusPuzzle::RemoveFirstRightObjects()
{
	auto currentFetus = AUXRightFetus[0];
	
	auto rand = FMath::RandRange(0, AUXPossiblePosition.Num() - 1);
	auto currentTarget = AUXPossiblePosition[rand];
		
	currentFetus->SetActorLocation(currentTarget->GetActorLocation());
	currentFetus->SetActorRotation(currentTarget->GetActorRotation()+ FRotator(0,-90,0));
		
	auto EndAuxTarget = AUXPossiblePosition[AUXPossiblePosition.Num()-1];
	AUXPossiblePosition[AUXPossiblePosition.Num()-1] = currentTarget;
	AUXPossiblePosition[rand] = EndAuxTarget;
	AUXPossiblePosition.RemoveAt(AUXPossiblePosition.Num()-1);


	auto EndAuxFetus = AUXRightFetus[AUXRightFetus.Num()-1];
	AUXRightFetus[AUXRightFetus.Num()-1] = currentFetus;
	AUXRightFetus[0] = EndAuxFetus;
	AUXRightFetus.RemoveAt(AUXRightFetus.Num()-1);
}
#pragma endregion