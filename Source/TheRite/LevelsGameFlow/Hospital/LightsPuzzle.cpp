//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "LightsPuzzle.h"
#include "TheRite/AlexPlayerController.h"
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

void ALightsPuzzle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	PuzzleCompleteTimerDelegate.Unbind();

	if (GetWorld()->GetTimerManager().IsTimerActive(PuzzleCompleteTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(PuzzleCompleteTimerHandle);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPuzzle::CheckPuzzleState()
{
	for (auto current : PortraitsInPuzzle)
	{
		if (!current->GetCurrentCorrectState()) return;

		auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
		controller->PlayRumbleFeedBack(.5f, .3, true, true, true, true);
	}

	PuzzleCompleted();
}

//----------------------------------------------------------------------------------------------------------------------
void ALightsPuzzle::PuzzleCompleted()
{
	for (auto current : PortraitsInPuzzle)
	{
		current->SetCanInteract(false);
		current->DisbalePortrait();
	}

	if(GetWorld()->GetTimerManager().IsTimerActive(PuzzleCompleteTimerHandle)) return;

	PuzzleCompleteTimerDelegate.BindLambda([this]()
		{
		OnPuzzleComplete.Broadcast();
		});
	

	GetWorld()->GetTimerManager().SetTimer(PuzzleCompleteTimerHandle, PuzzleCompleteTimerDelegate, 3.5f, false);
}