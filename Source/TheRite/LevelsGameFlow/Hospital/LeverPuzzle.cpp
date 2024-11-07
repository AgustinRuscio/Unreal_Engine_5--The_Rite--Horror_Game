//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "LeverPuzzle.h"
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
	if(!static_cast<ALever*>(interactor)->IsCorrect())
	{
		bPuzzleCorrect = false;
	}

	InteractionCounter++;

	CheckPuzzleEnd();
}

void ALeverPuzzle::DisableLevers(ALever* interactor)
{
	for (auto var : AllLevels)
	{
		if(interactor == var) continue;
		var->Deactivate();
	}
}

void ALeverPuzzle::EnableLevers(ALever* interactor)
{
	for (auto var : AllLevels)
	{
		if(interactor == var) continue;
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
void ALeverPuzzle::PuzzleCompleted() const
{
	OnPuzzleCompleted.Broadcast();
	
	for (auto var : AllLevels)
	{
		var->Destroy();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALeverPuzzle::PuzzleFailed()
{
	for (auto var : AllLevels)
	{
		var->ResetLever();
	}

	bPuzzleCorrect	   = true;
	InteractionCounter = 0;
}