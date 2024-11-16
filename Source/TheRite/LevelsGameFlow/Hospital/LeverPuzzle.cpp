//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "LeverPuzzle.h"

#include "Kismet/GameplayStatics.h"
#include "TheRite/Interactuables/Interactor.h"
#include "TheRite/Interactuables/Lever.h"

//----------------------------------------------------------------------------------------------------------------------
ALeverPuzzle::ALeverPuzzle() : bPuzzleCorrect(true), CorrectAmount(0), InteractionCounter(0)
{
	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ALeverPuzzle::BeginPlay()
{
	Super::BeginPlay();

	for (auto var : AllLevels)
	{
		var->OnInteractionTrigger.AddDynamic(this, &ALeverPuzzle::CheckLever);
		var->OnLeverUsageEnd.AddDynamic(this, &ALeverPuzzle::EnableLevers);
		var->OnLeverUsageStart.AddDynamic(this, &ALeverPuzzle::DisableLevers);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALeverPuzzle::CheckLever(class AInteractor* interactor)
{
	auto auxLever = static_cast<ALever*>(interactor);
	
	if(!auxLever->IsCorrect())
	{
		bPuzzleCorrect = false;
	}
	
	AuxUsedLevers.Add(auxLever);
	InteractionCounter++;

	CheckPuzzleEnd();
}

//----------------------------------------------------------------------------------------------------------------------
void ALeverPuzzle::DisableLevers(ALever* interactor)
{
	for (auto var : AllLevels)
	{
		if(interactor == var) continue;
		var->Deactivate();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALeverPuzzle::EnableLevers(ALever* interactor)
{
	for (auto var : AllLevels)
	{
		if(interactor == var) continue;
		if(AuxUsedLevers.Contains(var)) continue;
		var->Activate();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALeverPuzzle::CheckPuzzleEnd()
{
	if(InteractionCounter < CorrectAmount) return;

	if(bPuzzleCorrect)
		PuzzleCompleted();
	else
		PuzzleFailed();
}

//----------------------------------------------------------------------------------------------------------------------
void ALeverPuzzle::PuzzleCompleted()
{
	OnPuzzleCompleted.Broadcast();

	AuxUsedLevers.Empty();
	for (auto var : AllLevels)
	{
		var->Destroy();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALeverPuzzle::PuzzleFailed()
{
	AuxUsedLevers.Empty();
	for (auto var : AllLevels)
	{
		var->ResetLever();
	}

	UGameplayStatics::PlaySound2D(GetWorld(), PuzzleFailSound);
	bPuzzleCorrect	   = true;
	InteractionCounter = 0;
}