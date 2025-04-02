//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "LightsPuzzle.h"
#include "TheRite/Interactuables/LightsPortrait.h"

//----------------------------------------------------------------------------------------------------------------------
ALightsPuzzle::ALightsPuzzle()
{
 	PrimaryActorTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPuzzle::BeginPlay()
{
	Super::BeginPlay();

	for (auto current : PortraitsInPuzzle)
	{
		current->OnLightChange.AddDynamic(this, &ALightsPuzzle::CheckPuzzleState);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPuzzle::CheckPuzzleState()
{
	for (auto current : PortraitsInPuzzle)
	{
		if (!current->GetCurrentCorrectState()) return;
	}

	PuzzleCompleted();
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPuzzle::PuzzleCompleted()
{
	for (auto current : PortraitsInPuzzle)
	{
		current->SetCanInteract(false);
	}

	CompletePuzzleFeedBack();

	OnPuzzleComplete.Broadcast();
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPuzzle::CompletePuzzleFeedBack()
{

}